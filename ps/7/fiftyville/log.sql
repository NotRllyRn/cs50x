-- Keep a log of any SQL queries you execute as you solve the mystery.

-- i wanted to read all the transcripts of the interviews to see what people had to say
select * from interviews;

-- realized it was too big to read it all so i will limit it to 5
select * from interviews limit 5;

-- the data is not sorted for me so i will get all the interviews that were past july 28th
select * from interviews where month >= 7 and day >= 28;

-- Ruth saw the theif get into a car from the bakery parking lot and drove away
-- Eugene saw the theif withdrawing money at the atm on leggett street
-- Raymond saw the theif leave the bakery and call someone. He heard the theif say that they were going to take a plane out of fiftyville tomorrow

-- i want to see the description for the specfific crime scene of the stealing of the duck
select description from crime_scene_reports where month = 7 and day = 28 and street = "Chamberlin Street";

-- i saw nothing that came up from the query above so i decided to see everything that happened on the day of the crime
select * from crime_scene_reports where month = 7 and day = 28;

-- i am going to investiage what eugene saw and see if there wasy any transactions on leggett street
select atm_location from atm_transactions where month => 7 and day => 28;

-- a lot of people have made transactions so im going to limit it down
select atm_location from atm_transactions where month = 7 and day = 28;

-- this is not showing a lot of info and its still a lot of text so i will limit it down even more
select * from atm_transactions where month = 7 and day = 28 and atm_location = "Leggett Street";

-- there seems to be quite a few withdraws from leggett street on the day of the crime and only 1 deposit but i will list out all the data and specify the transaction type
-- im going to try to list all the names of the accounts from the people who have done transactions
select distinct name, transaction_type from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id;

-- i forgot to sort out when it happens
select distinct name, transaction_type from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street";

-- previous query returned a list of names so the current suspects that withdrew money are
-- Luca
-- Kenny
-- Taylor
-- Bruce
-- Brooke
-- Kaelyn (deposited money)
-- Iman
-- Benista
-- Diana

-- since the interviews talked about the suspect driving away and also making a phone call, im going to query to get the list of suspect's phone numbers and license plate numbers
select distinct name, phone_number, license_plate from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street";

-- i am too lazy to write it all down so here is the stuff directly outputed from the prompt
-- +---------+----------------+---------------+
-- |  name   |  phone_number  | license_plate |
-- +---------+----------------+---------------+
-- | Luca    | (389) 555-5198 | 4328GD8       |
-- | Kenny   | (826) 555-1652 | 30G67EN       |
-- | Taylor  | (286) 555-6063 | 1106N58       |
-- | Bruce   | (367) 555-5533 | 94KL13X       |
-- | Brooke  | (122) 555-4581 | QX4YZN3       |
-- | Kaelyn  | (098) 555-1164 | I449449       |
-- | Iman    | (829) 555-5269 | L93JTIZ       |
-- | Benista | (338) 555-6650 | 8X428L0       |
-- | Diana   | (770) 555-1861 | 322W7JE       |
-- +---------+----------------+---------------+

-- ruth saw that the theif got away in a car from the bakery parking lot so we are going to check the bakery security logs which includes the license plates of cars
select distinct name, activity, minute, hour from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join bakery_security_logs a on a.license_plate = people.license_plate
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and a.day = 28
and a.month = 7
order by hour, minute;

-- +---------+----------------+---------------+
-- |  name   |  phone_number  | license_plate |
-- +---------+----------------+---------------+
-- | Luca    | (389) 555-5198 | 4328GD8       | came
-- | Kenny   | (826) 555-1652 | 30G67EN       |
-- | Taylor  | (286) 555-6063 | 1106N58       | came
-- | Bruce   | (367) 555-5533 | 94KL13X       | came
-- | Brooke  | (122) 555-4581 | QX4YZN3       |
-- | Kaelyn  | (098) 555-1164 | I449449       |
-- | Iman    | (829) 555-5269 | L93JTIZ       | came
-- | Benista | (338) 555-6650 | 8X428L0       |
-- | Diana   | (770) 555-1861 | 322W7JE       | came
-- +---------+----------------+---------------+

-- our new suspect list is
-- Luca
-- Taylor
-- Bruce
-- Iman
-- Diana

-- i think its safe to search the phone table now
-- i didn't quite understand how the phone calls table was working so i had to look at the inside of it first
select * from phone_calls limit 5;

-- so it gives phone numbers, that makes more sense

-- trying to match the people up
-- this will find out who called who and it will show whom the suspects called
select distinct people.name, a.name from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join phone_calls on phone_calls.caller = people.phone_number
join people a on a.phone_number = phone_calls.receiver
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and phone_calls.day = 28
and phone_calls.month = 7;

-- Luca
-- Taylor phoned angela, james
-- Bruce phones gregory, deborah, robin, carl
-- Iman
-- Diana phones philip (main suspect?)

-- so it looks like luca and iman is no longer on the suspect list
-- also kenny did phone doris and benista did phone anna so we should look out fo that

-- once again i find nothing usefull here so i will look at the airports and flights to see who took off the next day
select name, airports.city, a.city from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join passengers on people.passport_number = passengers.passport_number
join flights on flights.id = passengers.flight_id
join airports on flights.origin_airport_id = airports.id
join airports a on flights.destination_airport_id = a.id
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and flights.day = 29
and flights.month = 7
order by name, flights.hour, flights.minute;

-- Taylor leaves
-- Bruce leaves
-- Diana leaves

-- i realized i must have missed some data so im going to look at crime scene reports again
select * from crime_scene_reports where month = 7 and day = 28;

-- this is the report:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- so i need to look at the times that our current suspects entered and left the bakery
select distinct name, activity, minute, hour from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join bakery_security_logs a on a.license_plate = people.license_plate
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and a.day = 28
and a.month = 7
order by hour, minute;

-- bruce left at 10:18 ( 3 minutes after crime )
-- taylor left at 10:35 ( 20 minutes after crime )
-- diana left at 10:23 ( 8 minutes after crime )

-- i feel like maybe if we look at the duration of the phone calls they made, we can see what time they "should have left"
select distinct people.name, a.name, duration from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join phone_calls on phone_calls.caller = people.phone_number
join people a on a.phone_number = phone_calls.receiver
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and phone_calls.day = 28
and phone_calls.month = 7;

-- Taylor talks for a total of 278 seconds
-- Bruce talks for 481 seconds
-- Diana talks for 49 seconds

-- so bruced talked way longer than 3 minutes so i think that means that they could have not stolen the duck.
-- its either diana or taylor because taylor left super late.

-- i decided to look at the interviews again to see if left any detail out
select * from interviews where month >= 7 and day >= 28;

-- Ruth said that "within 10 minutes of the theft" he saw that they got into the car and drove away.
-- Eugene recognized the person so maybe the person called eugene.
-- Raymond said they called with someone for less than a minute.
-- Raymond says that they wanted to take the earliest flight out of town tommorrow and also that the theif told the person on the other end to make the purshace of the flight ticket

-- this is really useful information

-- i wanted to look at the suspects to see how long they called the people
select distinct people.name, a.name, duration from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join phone_calls on phone_calls.caller = people.phone_number
join people a on a.phone_number = phone_calls.receiver
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and phone_calls.day = 28
and phone_calls.month = 7;

-- Taylor talked to james for 43 seconds
-- Bruce talked to robin for 45 seconds
-- Diana talked to philip for 49 seconds

-- so that could be the possible acomplices
-- now lets look at the bakery security logs to see when the theif left because Ruth said that they left about 10 minutes after the theif and we know the theif was taken place around 10:15
select distinct name, activity, minute, hour from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join bakery_security_logs a on a.license_plate = people.license_plate
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and a.day = 28
and a.month = 7
order by hour, minute;

-- i wanted to refresh my memory so im going to look at the interviews
select * from interviews where month >= 7 and day >= 28;

-- Eugene said that before they saw she arrived at the bakery they saw the theif withdraw money

-- i am going to look at the transactions to see if i missed anything
select distinct name, transaction_type from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street";

-- since the theif told their acomplice to purchase a plane ticket the next day, maybe their acomplice withdrew a large sum
-- lets check the day of the theif and the next day's withdraws
select distinct name, transaction_type, amount from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street";

-- it looks like the largest amount that was withdraw was just 80 dollars by brooke, but that is not a lot
-- lets check the next day
select distinct name, transaction_type, amount from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
where atm_transactions.month = 7
and atm_transactions.day = 29
and atm_transactions.atm_location = "Leggett Street"
order by transaction_type, amount;

-- christina billy and margaret all withdrew 95 the next day
-- since eugene did recognize the person, maybe eugene calls that person a lot so lets look at all the calls that eugene has made

-- first i want to try to get eugenes phone number
select phone_number from people where name = "Eugene";

-- now i want to try to link the phones table to see all the calls eugene has made
select caller, receiver from phone_calls
where caller =
(select phone_number from people where name = "Eugene");

-- well it looks like that eugene only called 3 people
-- lets convert those into names
select a.name, b.name from phone_calls
join people a on a.phone_number = caller
join people b on b.phone_number = receiver
where caller =
(select phone_number from people where name = "Eugene");

-- eugene has only called justin raymond and maria.
-- that doesn't really help.

-- raymond said they were going to take the earliest flight out of town tommorrow, so we should sort the flights for the 29th and see what is the first flight out
select name, a.City, b.City, minute, hour from flights
join airports a on flights.origin_airport_id = a.id
join airports b on flights.destination_airport_id = b.id
join passengers on passengers.flight_id = flights.id
join people on people.passport_number = passengers.passport_number
where a.City = "Fiftyville"
and not b.City = "Fiftyville"
order by hour, minute;

-- the earliest flight out of town was to chicago but no one on that lfight was in our original suspect list

-- oh i realized i didn't check the day of leaving so i need to set it to 29th lol
select name, a.City, b.City, minute, hour from flights
join airports a on flights.origin_airport_id = a.id
join airports b on flights.destination_airport_id = b.id
join passengers on passengers.flight_id = flights.id
join people on people.passport_number = passengers.passport_number
where a.City = "Fiftyville"
and not b.City = "Fiftyville"
and flights.day = 29
and flights.month = 7
order by hour, minute;

-- so the first flight out of town was new york city

-- from our current suspect list
-- Taylor
-- Bruce
-- left on the earliest fight

-- okay so now we only have 2 people to check
-- going back to my notes and i decided to look at the interviews again
select * from interviews where month >= 7 and day >= 28;

-- i think im not going to check when everyone left the bakery because appearently they left 10 minutes after it happened
select distinct name, activity, minute, hour from atm_transactions
join bank_accounts on atm_transactions.account_number = bank_accounts.account_number
join people on bank_accounts.person_id = people.id
join bakery_security_logs a on a.license_plate = people.license_plate
where atm_transactions.month = 7
and atm_transactions.day = 28
and atm_transactions.atm_location = "Leggett Street"
and a.day = 28
and a.month = 7
order by hour, minute;

-- since bruce left 3 minutes after the crime happened, he could not be a suspect since ruth saw the theif leave after 10 minutes
-- that only leaves taylor as the theif!
-- i think taylor's acomplice is james since they talked together on the day of the crime for less than a minute

-- i just did check50 and it said i solved the mystery wrong
-- i think that it might be bruce because now that i think of it, raymond said the theif left within 10 minutes, not after 10 minutes
-- Bruce left 3 minutes after the theft and also called robin for less than a minute

-- so i think the theif is bruce and the acomplice is robin

-- I GOT IT RIGHT! :)