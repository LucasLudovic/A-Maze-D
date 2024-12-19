# Amazed

Amazed is a C project designed to simulate a scenario where a certain number of mice need to traverse through various rooms to reach the exit, ensuring each room is visited by only one mouse at a time. The objective is to reach the exit with the fewest possible moves, utilizing Breadth-first search algorithm for pathfinding.

## Input Format

```
#number_of_robots
<Number of mice>
#rooms
<Room IDs separated by spaces>
##start
<Start room ID coordinates>
##end
<End room ID coordinates>
<Room connections>
#tunnels
<Tunnel connections between rooms>
#moves
<Moves made by mice>
```

### Example

```shell
B-CPE-200> ./amazed < labyrinth
#number_of_robots
3
#rooms
2 5 0
##start
0 1 2
##end
1 9 2
3 5 4
#tunnels
0-2
0-3
2-1
3-1
2-3
#moves
P1-2 P2-3
P1-1 P2-1 P3-2
P3-1
```

### Usage

Compile the program using a C compiler, such as GCC.
Create an input file named "labyrinth" in the specified format.
Run the program, providing the input file as input.

### bash
```shell
make
./amazed < labyrinth
```

### Features
Utilizes Breadth-first search algorithm for optimal pathfinding.
Ensures each room is visited by only one mouse at a time.
Calculates the shortest path for mice to reach the exit.
Input file specifies the number of mice, rooms, room connections, tunnels, and moves made by mice.

### Technologies

- <small>[![My Skills](https://skillicons.dev/icons?i=c)](https://skillicons.dev) </small>
- <small>[![My Skills](https://skillicons.dev/icons?i=github)](https://skillicons.dev) </small>

## Contributors

- [Jimmy](https://github.com/JimmyRamsamynaick)
- [Tilio](https://github.com/TilioHuart)
- [Lucas](https://github.com/LucasLudovic)
