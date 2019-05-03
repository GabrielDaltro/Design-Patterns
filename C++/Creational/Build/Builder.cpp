/*
Gabriel Daltro Duarte

Implementation of Builder Design Pattern.
Example taken from GoF Book

*/

//Enun that represents the four directions
enum Direction {North, South, East, West};

/* MapSite is a abstract class that represents all maze objects
*/
class MapSite
{
    public:
       virtual void Enter (void) = 0;
};

/* Room is a concrete derived class of MapSite that represents maze's rooms
*/
class Room: public MapSite
{
    public:
        // Constructor method
        Room (int roomNumber) {/* Implementation */ }
        // GetInside method default implementation
        MapSite* GetInside (Direction) const {/* Implementation */ }
        // SetSide method default implementation
        void SetSide (Direction, MapSite* )  {/* Implementation */}
        // Override of Enter method
        virtual void Enter (void){/* Implementation */ }
    private:
        MapSite* _sides[4];
        int _roomNumber;
};

/* Wall is a concrete derived class of Abstract MapSite class that represents maze's wall
*/
class Wall: public MapSite
{
    public:
        //Constructor
        Wall(){/* Implementation */ }
        // Override of Enter method
        virtual void Enter (){/* Implementation */}
};


/* Door is a concrete derived class of Abstract MapSite class that represent a door between maze's room
*/
class Door: public MapSite
{
    public:
        //Constructor
        Door (Room* = 0, Room* = 0) {/* Implementation */}
        //Override of Enter method
        virtual void Enter(){/* Implementation */}
        // Default implementation of OtherSideFrom
        Room* OtherSideFrom(Room*){/* Implementation */}

    private:
        Room* _room1;
        Room* _room2;
        bool isOpen;
};

/*Maze is a class that represents a Maze
*/
class Maze
{
    public:
        Maze(){/* Implementation */}

        void addRoom(Room*) {/* Implementation */}
        Room* RoomNo (int) const {/* Implementation */}

    private:
        /* private attributes*/

};


class MazeBuilder // Builder Interface - It can creates mazes, rooms and doors
{
    public:
        virtual void BuildMaze() {}
        virtual void BuildRoom(int) {}
        virtual void BuildDoor (int roomFrom, int roomTo) {}

        virtual Maze* getMaze() {return 0;}

    protected:
        MazeBuilder();
};

class StandardMazeBuilder: public MazeBuilder // concrete Builder
{
    public:
        StandardMazeBuilder () {
            _currentMaze = 0;
        }
        void BuildMaze (){
            _currentMaze = new Maze();
        }
        Maze* getMaze (){
            return _currentMaze;
        }
        void BuildRoom (int n){
            if (! _currentMaze->RoomNo(n)){
                Room* room = new Room(n);
                _currentMaze->addRoom(room);
                room->SetSide(North,new Wall());
                room->SetSide(South,new Wall());
                room->SetSide(West,new Wall());
                room->SetSide(East,new Wall());
            }
        }
        void BuildDoor (int n1, int n2){
            Room* r1 = _currentMaze->RoomNo(n1);
            Room* r2 = _currentMaze->RoomNo(n2);

            Door* door = new Door (r1,r2);

            r1->SetSide(commomWall(r1,r2),door);
            r2->SetSide(commomWall(r2,r1),door);
        }

    private:
        Direction commomWall(Room*, Room*){}
        Maze* _currentMaze;
};


class MazeGame { // Director
    public:
        Maze* createMaze (MazeBuilder& builder){
            builder.BuildMaze(); // build object part 1
            builder.BuildRoom(1);// build object part 2
            builder.BuildRoom(2);// build object part 3
            return builder.getMaze(); // return a constructed object
        }

} ;


int main() // client
{

    StandardMazeBuilder stdMazeBuilder; // creates a reference to concrete builder
    MazeGame game; // creates the director
    game.createMaze (stdMazeBuilder); // construct the object

    Maze* maze = stdMazeBuilder.getMaze();// get Result()

    return 0;
}














