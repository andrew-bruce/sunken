# Game Design Document
Andrew Bruce and Scott Davidson

[![Build status](https://ci.appveyor.com/api/projects/status/kjop6vl5bp3f2eue?svg=true)](https://ci.appveyor.com/project/abruce1711/sunken/branch/engine-implentation)

# Document History


<table>
  <tr>
   <td><strong>Version</strong>
   </td>
   <td><strong>Author</strong>
   </td>
   <td><strong>Date</strong>
   </td>
   <td><strong>Comments</strong>
   </td>
  </tr>
  <tr>
   <td>1
   </td>
   <td>Scott Davidson and Andrew Bruce
   </td>
   <td>28/02/2019
   </td>
   <td>Completed first version of GDD
   </td>
  </tr>
</table>





# Overview and Vision Statement

Sunken is 2D, side scrolling, submarine war game which makes heavy use of audio visulisation. This will mean that the player can only see what their sonar can detect; they will need to use this carefully to navigate dangerous terrain and avoid or defeat enemies. The player will eventually reach and destroy an objective. Enemies can come in the form of submarines which will fire torpedos or ships which will drop depth charges. The player will need to conserve resources throughout the game: replenishing ammo using pickups throughout the level and trying to beat the level as fast as possible for a higher score. They will also need to account for their health as the lower it gets the more difficult it will be to stay buoyant.


# Inspirations

Sunken is  inspired by a World War 2 based 3D submarine game called Cold Waters, which makes use of audio visulisation making sound a core feature of the game. It creates a suspenseful atmosphere that does well to go along with the topic of the game.


# Player Experience Goals



*   Players should feel challenged as they will need to navigate the level with limited vision, making decisions about whether to avoid or engage enemies, all while being timed
*   They should also feel suspense when playing the game; the audio visual element will hide the threats. The in-game music should amplify this emotion
*   The player will feel a sense of accomplishment upon successfully navigating the level, defeating an enemy, and completing the objective


# Audience and Platform



*   Sunken's target demographic are people who like tense strategy action games, likely ages 10+. The potential size of this audience is large as the game is relatively simple in terms of scope, making it more accessible
*   The target platform will be PCs running Windows or Linux
*   Any modern PC will be able to run the game as it is relatively small. They will require either a mouse and keyboard or a controller


## Legal Analysis



*   Possible licence issues with the game music or other sounds
*   Both SFML and Box2D follow the same terms of use, as below - 
    *   "The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required."
    *   "Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software."
    *   "This notice may not be removed or altered from any source distribution."
*   Possible IP issues from use of game sprites


# Gameplay


## Overview



*   Navigate levels using sound (visualised) to get to and destroy a final objective
*   Engage in combat with enemies or use stealth to avoid combat
*   Manage resources such as ammo for combat, health for survivability and time for score \



### Player Mode

Sunken is a single player game, battling against AI enemies.


## Screen Mockup

![mockup](https://user-images.githubusercontent.com/32868831/55109200-26253080-50cd-11e9-9e38-8a6637f175a7.png)



## Formal Elements


### Players

There will be one player, playing as the submarine. They will play against enemy AI submarines and ships.


### Objectives



*   Destroy the objective at the end of the level
*   Defeat enemy ships and submarines
*   Conserve resources and use as little ammunition as possible
*   Complete the level in the shortest amount of time


### Procedures


### Rules



*   if player/enemy health is 0 player/enemy dies
*   if player touches ammo box ammo increases
*   if player/enemy touches torpedo/depth charge, player/enemy health decreases
*   if player/enemy touches wall and player/enemy speed is high, player/enemy health decreases
*   if player/enemy health less than x and player/enemy depth less than y, player/enemy sinks
*   if player detects enemy sonar, show direction
    *   if torpedo sonar, show colour based on torpedo stage (seeking, locking, terminating)
*   if enemy detects player sonar, change state to attack
*   if enemy detects torpedo, snapshot and change state to evade
*   if enemy cannot detect player anymore, change state to alert
    *   if enemy still cannot detect player, return state to patrol
*   enemy base destroyed, player wins
*   enemy base detects player, change state to attack
*   enemy base detects torpedo, snapshot and change state to alert
*   if ship detects player, move and drop depth charge


### Resources



*   Health
*   Ammunition
*   Time
*   Noise
*   Depth


### Conflict



*   Obstacles
    *   Terrain
    *   Depth to avoid ships
*   Opponents
    *   Enemy ships
    *   Enemy submarines
    *   Enemy base
*   Dilemmas
    *   Choosing to fight or avoid depending on resources (ammo, health, time)


### Boundaries

There will be physical 2D world boundaries to prevent the player from going above the water or outside the level.


### Outcome

If the player health reaches zero the player will lose and restart the level. If the enemy base health reaches 0 the player will win and complete the level. Once the player completes all story levels they will have completed the game. Custom levels are independent of game progression, however, they should follow the same outcomes.


## Levels

The default levels will be included in the code so they cannot be edited by users. There will also be a levels folder for users to create their own levels and share them with friends.

The levels will be tile based and side scrolling with varying degrees of difficulty.


## Characters



*   The main character will be the submarine the player is in command of
*   The commanding officer who relays the objective at the start of the default levels
*   The enemy submarines and ships who attempt to destroy the player
*   The base, which will attempt to defend itself from the players attack


## Story

The game will have a brief description of the objective at the beginning of each level, relayed by the submarines commanding officer. 


## Game World



*   Enemy infested waters
*   Cave systems
*   Key locations -
    *   Enemy bases
    *   Ammo pickups
    *   Enemy patrol points
*   Underwater physics


# Required Media List


<table>
  <tr>
   <td><strong>Name</strong>
   </td>
   <td><strong>Description</strong>
   </td>
  </tr>
</table>



## User Interface Assets


<table>
  <tr>
   <td>Super Submarine
   </td>
   <td>Font for score, time, depth, noise, and menu
   </td>
  </tr>
  <tr>
   <td>Button styles
   </td>
   <td>Button images
   </td>
  </tr>
</table>



## Environment Assets


<table>
  <tr>
   <td>Tile sprites
   </td>
   <td>Different sprites for different tile types
   </td>
  </tr>
  <tr>
   <td>Ammo pickup sprite
   </td>
   <td>A sprite depicting an ammo pickup
   </td>
  </tr>
  <tr>
   <td>Background image
   </td>
   <td>An image to depict that the character is in the water
   </td>
  </tr>
</table>



## Character-based Assets


<table>
  <tr>
   <td>Submarine sprites
   </td>
   <td>Depicting submarines
   </td>
  </tr>
  <tr>
   <td>Ship sprites
   </td>
   <td>Depicting ships
   </td>
  </tr>
  <tr>
   <td>Enemy base sprite
   </td>
   <td>Depicting the enemy base
   </td>
  </tr>
</table>



## Music Assets


<table>
  <tr>
   <td>Background music
   </td>
   <td>Suspenseful background music
   </td>
  </tr>
</table>



## Sound Effect Assets


<table>
  <tr>
   <td>Sonar sound effect
   </td>
   <td>When the player uses/detects sonar
   </td>
  </tr>
  <tr>
   <td>Torpedo sound effect
   </td>
   <td>When a player/enemy fires a torpedo
   </td>
  </tr>
  <tr>
   <td>Explosion sound effect
   </td>
   <td>When the player, an enemy, or base explodes
   </td>
  </tr>
  <tr>
   <td>Crashing sound effect
   </td>
   <td>When the a submarine crashes into the terrain
   </td>
  </tr>
  <tr>
   <td>Ammo pickup sound effect
   </td>
   <td>When a player picks up ammo
   </td>
  </tr>
  <tr>
   <td>Cavitation sound effect
   </td>
   <td>When a player goes too fast for their depth
   </td>
  </tr>
</table>



# Technical Specification


## Development Platform and Tools



*   Platform:
    *   Windows
    *   Linux
*   IDE:
    *   Visual Studio 2017
    *   Visual Studio code
*   Compiler:
    *   MSVC
    *   G++
*   Build tools:
    *   CMake
*   Libraries:
    *   SFML
    *   Box2D
*   Language:
    *   C++
*   Version Control tools:
    *   Git
    *   Github Desktop
    *   Sourcetree
    *   Github


## Delivery Mechanism

The game will be distributed via itch.io and GOG.com as they a free to publish and DRM free for users.


## User Interface Technical Requirements

A minimum resolution of 800 x 600 will be required.


## Controls Technical Specification

The controls will require a keyboard and mouse or controller.


## Network Requirements

Sunken is a single player game that will not require a network connection.


## Menu Flowchart

![flow chart](https://user-images.githubusercontent.com/32868831/55109223-33dab600-50cd-11e9-95df-05b87b670b2d.png)
