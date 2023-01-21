# Mooving Cattle
#### Video Demo:  [Here](https://youtu.be/qgStcKaILbI)
#### Description: A game set in the 1890s about a player who takes a herd through the desert to sell all the cattle per pound.

# LoveLua files

These files are required to run a love2d lua game. I quickly explain what happens inside of them

- ## main.lua

This file is responsible for keeping track of every game state and rendering / drawing everything correctly.

It also holds constants and the current game data. It loads all the modules and handels all the inputs from the player

- ## conf.lua

This file contains default settings for the game, so when it is loaded it will allow the game to be rendered at different resolutions.

# Modules

All of these modules are responsible for their own things and there are a lot of them, so i will mention the most notible ones.

- ## data.lua

This module uses a serilizer to take in a table and convert it to a string. It can also read data form the serilized data. The module handles data saving and loading.

- ## class.lua

This modules allows for me to create objects with methods and data and have new objects / classes that inherites it. Very useful for OOP programming

- ## mr.lua

This module is the most helpful out of them all. It handles translating and scalling the game so that i can maintain the game at the same resolution. It will automatically add black bars on the top and bottom and lets me draw objects without worrying where they should be.

# assets

This folder contains a lot of images for the character and backgrounds. It also contains code for certain things in the game like events and states of the game.

There are 3 folders within the assets folder.
- events
- objects
- states

---
## events

This folder contains code for certain events that will happen. each file inside has a load, update, and sometimes a draw function. If the event requires it, it will also have functions like keypressed and such.

Each file also holds the chance that the event will happen.

## objects

This folder contains the code for all the objects that can be made. All of them have a load, update, and draw function and somtimes a keypresssed function.

There are objects like cows, players, text and even buttons.

I put them into seperate files and made them into objects so i can easily create them without having to copy and paste a lot of code.

## states

This folder is the most important as it holds the multiple states for the game. Each state has a function called load, update, draw, and keypressed. The main love events need to be passed to the states.

These states are responsible what is happening on the screen at the moment and what should be happening off screen with calculations and such.

---

# The process

## The start

I went through 2 versions of the game and decided to pick the 2nd version as the final version.

When i made the first version, i didn't use MR, which stands for multi resolution. I started to make an infinite background loop and soon found out that it was going to be very hard to make it work even if the user changes resolutions

I was pretty sure i would have to make my own module for everything like a coordinate system and sizing system for images and objects.

I decided to restart and i started to use mr instead.

## Icons

I wanted to make this game entirely by myself, that included by drawing all the icons. I have never been good at drawing or pixel art but i tried my best. I wanted to get the experience of making it all on my own.

I used Paint3d for all my pixel art and quickly learned how to use all its tools to draw to the best of my ability.

## Structure of code

The structure of code i ended up with is very good. I am very happy with it and i think it is very easy to add features and have have multiple things communicate together.

The reason why it worked so well is because I decided to modulize everything. Instead of putting all the states into the main.lua file and just doing a state check using if elseif, i decided to put everything into different files into 1 folder. This way i would only have to look at 1 file at a time.

In the end, this made my code a lot cleaner and easier to understand.

---
# How to play

There are a total of 6 keys you will press whilst playing the game.
WASD for movement, E for interactions and shift for dashing.

You will also move and click your mouse for menu interactions.

To pause the game, press the ESC key.

- ## Wandering cows

To avoid losing your cows as they roam off, you have to ride up to them and press E.

- ## Wolves attack

Wolves will come in packs of 2-5. They will go to one of your cows and start to attack them.

You will know when the wolves are attacking your cow when there is a wolf head icon above the cow.

To stop them from attacking your cow, you need to walk up to them and press E a certain # of times.

- ## Alien Encounter

A very rare encounter.

- ## Dashing with the horse

Holding down a movement key and pressing shift will let you dash in that direction. There is a cooldown!

- ## At the end

There is a calculation of how many pounds of cow you have and a random conversion rate and you earn coins.

- ## Overal

Protect your cows and sell them for profit!