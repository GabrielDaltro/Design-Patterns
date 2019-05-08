/*
Gabriel Daltro Duarte

Implementation of Factory Method Design Pattern.
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

/* RoomWithABomb is a derived class of Room that represents a maze's Rooms that can have a bomb
*/
class RoomWithABomb: public Room
{
    public:
        // Constructor method
        RoomWithABomb (int roomNumber) :Room(roomNumber)
        {
            /* Implementation */
        }
        // Override of GetInside method
        MapSite* GetInside (Direction) const {/* Implementation */ }
        // Override of SetSide method
        void SetSide (Direction, MapSite* ) {/* Implementation */ }
        // Override of Enter method
        virtual void Enter (void) {/* Implementation */ }
    private:
        MapSite* _sides[4];
        int _roomNumber;
        bool hasIsAboom;
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
/* BombedWall is a derived class of Wall class that represents maze's wall that maintains the damage caused by a bomb
*/
class BombedWall: public Wall
{
    public:
        //Constructor
        BombedWall(){/* Implementation */ }
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

class MazeGame { // creator
    public:
        Maze* createMaze (){

          Maze* aMaze = MakeMaze();
          Room* r1 = MakeRoom(1);
          Room* r2 = MakeRoom(2);
          Door* aDoor = MakeDoor(r1,r2);

          aMaze->addRoom(r1);
          aMaze->addRoom(r2);

          r1->SetSide(North,MakeWall());
          r1->SetSide(South, MakeWall());
          r1->SetSide(West, MakeWall());
          r1->SetSide(East,aDoor);

          r2->SetSide(North,MakeWall());
          r2->SetSide(South,MakeWall());
          r2->SetSide(West, aDoor);
          r2->SetSide(East,MakeWall());

          return aMaze;
        }

        // factory methods
        virtual Maze* MakeMaze() const{
            return new Maze;
        }
        virtual Room* MakeRoom (int n) const {
            return new Room (n);
        }
        virtual Wall* MakeWall() const {
            return new Wall;
        }
        virtual Door* MakeDoor (Room* r1, Room* r2) const {
            return new Door (r1, r2);
        }
} ;

class BombedMazeGame: public MazeGame { // Concrete Creator
    public:
       BombedMazeGame() {/*implementation*/}

       virtual Wall* MakeWall () const {
            return new BombedWall;
       }
       virtual Room* MakeRoom (int n) const {
            return new RoomWithABomb(n);
       }
    private:

};


int main() // client
{
    Maze* aMaze;
    BombedMazeGame game;

    aMaze = game.createMaze();

    return 0;
}














