# Chess on steroids

PvP, outlive opponent to win

# Core:

## isometric camera


## square grid map
flat grid in 3d space (since we use UE)
8x8?

## player character
2d sprites
moving on 2.5d grid
no-hp

## same screen 2-player controls
2 player controllers on 1 client?

## predefined movesets
a type of move that can be done in different directions, similar to chess
move is configured as a series of transitions

#### movement
move is preshown on the grid for all directions
after move direction is selected move is processed
move processing takes small amount of time (<1s)
while move is processed player is considered staying on the starging tile
if the movement ends on the tile where another player is staying - that player dies

## score
score is given for killing another player



# Optional:

## movesets rotation
randomly generated list of movesets, moveset changes to the next one after the current move is processed
tetris-like view of next N movesets

## bubble-fog-of-war
fog of war appears on some part of the level
players under it can move but it covers them so they are hidden
it becomes half-transparent when both players are inside it

## power-ups
appear on the grid randomly
bubble-shield

