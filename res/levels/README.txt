- Levels are stored as text files
- Levels use symbols to represent different tiles
- Levels must have at least 1 start and end tile
- Levels should preferably have a path between them ;)
- Spaces will be ignored (easier to look at)

- Level keys are as follows
	@	player spawn
	.	water (submarines can traverse)
	~	air (battleships can traverse)
	#	wall/terrain
	+	health pickup
	=	ammo pickup
	*	enemy waypoints
	!	end objective/enemy base

	B = battleship
	S = submarine

Example below shows an 13x7 level:

# # # # # # # # # # # # #
# ~ ~ ~ # # # # ~ B ~ ~ #
# @ . . . # # # . . . . #
# . . # * S . . * # . . #
# . # # # # . # # # . . #
# . . = # # + # # # . ! #
# # # # # # # # # # # # #
