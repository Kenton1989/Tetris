# Data Dictionary

## Cell
- represents a square cell
- can be empty
- has apperance/texture information
- apperance info of an empty cell is meaningless
- has no position information

## Brick
- represents the brick falling from the top during the game
- is composed with *Cell*s, shape info and position info
- has the coordination of the "center" of brick
- the coordination of shape use the "center" as origin point
- can transform to another shape
- support adding cells
- support removing all cells, but not one specific cell
- maintain the max & min coordination of brick

## RectField
- represents the field where the brick fall through
- mainly used to maintain the organization of cell
- is composed with a metrix of *Cell*s
- support adding a *Brick* in to the Field, no cell conflict checking, 
  always overwrite cells when a brick is added
- support editing indivisual cell
- support checking whether a row is filled
- support removing one row or several rows at a time

## TetrisEngine
- control the overall game logic, includes
  - receiving input
  - managing timer
  - scoring
  - signaling modification
  - manage brick preview

## TetrisEngineBuilder
- used to generate a engine that satify a certain configuration, includes
  - field size
  - falling speed
  - number of brick preview