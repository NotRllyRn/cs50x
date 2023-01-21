import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get the rows of stocks that the user has and their cash
    stocks = db.execute("SELECT * FROM stock_purchases WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # start to calculate how much total cash they have
    # start a loop to go through all their owned stocks
    total = cash
    for stock in stocks:
        # look up the current prices of their stock
        stock_info = lookup(stock["symbol"])

        # calculate the total amount of money they have with this 1 stock
        # add the amount to the total we have including the cash
        amount = stock_info["price"] * stock["shares"]
        total += amount

        # convert the prices and amounts into readable prices for the user
        stock["total"] = usd(amount)
        stock["price"] = usd(stock_info["price"])

    # return the template and let jinja to make the html with the data
    return render_template("index.html", stocks=stocks, total=usd(total), cash=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # does something else if the method is POST
    if request.method == "POST":
        # get the symbol and shares
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # if symbol or shares is None then it will error to the user
        if not symbol or not shares:
            return apology("Provide a stock symbol and/or amount of shares.", 400)

        # makes sure that shares and symbols are correctly formatted
        try:
            shares = int(shares)
        except:
            return apology("Provide a valid amount of shares.", 400)

        symbol = symbol.upper()

        # gets the stocks information and errors the user if they provided an invalid stock or invalid amount of stocks
        info = lookup(symbol)
        if not info or shares < 1:
            return apology("Provide a valid stock symbol and/or valid amount of shares.")

        # gets the user information and calculates the total amount of money spent on the shares
        user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]
        total_spent = info["price"] * shares

        # checks if the user has enough money to buy the shares and errors if not
        if user_info["cash"] < total_spent:
            return apology("Not enough money.", 400)

        # calculates the amount the user now has with the bought stocks and updates their cash in the db
        new_cash = user_info["cash"] - total_spent
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

        # gets the current time of buying the stocks
        # gets the current amount of shares they have of symbol the user is buying
        time = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
        rows = db.execute("SELECT shares FROM stock_purchases WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])

        # if they do not have any of the current stocks they are buying then it will insert a new row
        if len(rows) != 1:
            db.execute("INSERT INTO stock_purchases (user_id, symbol, name, shares) VALUES(?, ?, ?, ?)",
                       session["user_id"], symbol, info["name"], shares)
        else:
            # else it will update the current row with the new amount of shares
            db.execute("UPDATE stock_purchases SET shares = ? WHERE user_id = ? AND symbol = ?",
                       rows[0]["shares"] + shares, session["user_id"], symbol)

        # log what just happened in the history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?)",
                   session["user_id"], symbol, shares, info["price"], time)

        # redirect back to the main page
        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get the history of the user and return it to the user
    # jinja formats the html
    history = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", info=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # check if its a post method
    if request.method == "POST":
        # gets the current symbol and errors to the user if its None
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Provide a stock symbol.", 400)

        # attempts to lookup the information for the stock
        # errors to the user if the stock does not exist
        info = lookup(symbol)
        if not info:
            return apology("Provide a valid stock symbol.", 400)

        # makes the price readable to the user in usd form and lets jinja format the html
        info["price"] = usd(info["price"])
        return render_template("quote.html", information=info)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # check if its a post method
    if request.method == "POST":
        # gets the username, password, and confirmation of the password
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # if they don't exist then it will error to the user
        if not username or not password or not confirmation:
            return apology("Must provide a username and password.", 400)

        # if the confirmation passwords don't match then error to the user
        if password != confirmation:
            return apology("Passwords do not match.", 400)

        # checks if the username the user is signing up for already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("Username taken.", 400)

        # hashes the password for the user and creates a new row for them making them a user
        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # gets the id of the user and sets it in the current session
        id = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = id[0]["id"]

        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # check if its a post method
    if request.method == "POST":
        # gets symbols and shares from the post request
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # error to the user if the symbols and shares are None
        if not symbol or not shares:
            return apology("Provide a stock symbol and/or # of shares.", 400)

        # makes sure the shares and symbols are properly formatted
        shares = int(shares)
        symbol = symbol.upper()

        # attempts to get the stocks the the user wants to sell
        # errors to the user if they do not own the stock
        rows = db.execute("SELECT shares FROM stock_purchases WHERE user_id = ? AND symbol = ?",
                          session["user_id"], symbol)
        if len(rows) < 1:
            return apology("You do not own this stock.", 400)

        # get the # of shares they have and if they have less then they want to sell then error the user
        amount = rows[0]["shares"]
        if amount < shares:
            return apology("You cannot sell more shares than you own.", 400)

        # gets the new amount of shares they will own
        new_amount = amount - shares
        if new_amount == 0:
            # deletes the row from the table if they won't have anymore shares
            db.execute("DELETE FROM stock_purchases WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            # updates the current row if they will still have shares.
            db.execute("UPDATE stock_purchases SET shares = ? WHERE user_id = ? AND symbol = ?",
                       new_amount, session["user_id"], symbol)

        # gets the current time for logging and gets the stock information
        time = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
        stock_info = lookup(symbol)

        # log to the history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?)",
                   session["user_id"], symbol, -shares, stock_info["price"], time)

        # gets the cash that the user currently has and adds the amount they earned from selling shares
        # updates the users row
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + (stock_info["price"] * shares), session["user_id"])

        return redirect("/")

    # gets the stocks that the user has and lets jinja format it in html for a list
    stocks = db.execute("SELECT * FROM stock_purchases WHERE user_id = ?", session["user_id"])
    return render_template("sell.html", stocks=stocks)


@app.route("/pchange", methods=["GET", "POST"])
@login_required
def pchange():
    """Change your password"""

    # checks if its a post request
    if request.method == "POST":
        # gets the current password, new password and its confirmation
        password = request.form.get("password")
        n_password = request.form.get("newpassword")
        c_password = request.form.get("confirm")

        # if they don't exist then error to the user
        if not password or not n_password or not c_password:
            return apology("Provide a valid password and/or new password and/or confirmation password.", 400)

        # if the new passwords do not match then error to the user
        if c_password != n_password:
            return apology("New passwords do not match.", 400)

        # gets the current has of the user and checks if the hashes match up (checks the passwords)
        hash = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"]
        if not check_password_hash(hash, password):
            return apology("Your password is wrong.", 400)

        # generates a new hash password for the user and sets their hash to change their password
        new_hash = generate_password_hash(n_password, method='pbkdf2:sha256', salt_length=8)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, session["user_id"])
        return redirect("/")

    return render_template("pchange.html")