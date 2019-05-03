

//Enun that represent the four directions
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

/* EnchantedRoom is a  derived class of Room that represents a maze's Enchanted Rooms
*/
class EnchantedRoom: public Room
{
    public:
         // Constructor method
        EnchantedRoom (int roomNumber):Room(roomNumber)
        {
            /* Implementation */
        }
        // Override of GetInside method
        MapSite* GetInside (Direction) const {/* Implementation */ }
        // Override of SetSide method
        void SetSide (Direction, MapSite* ){/* Implementation */ }
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

class DoorNeedSpell: public Door
{
    public:
        //Constructor
        DoorNeedSpell (Room* = 0,Room* = 0) {}
        //Override of Enter method
        virtual void Enter(){/* Implementation */}
        // Override of OtherSideFrom method
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

/* Room, Door and Wall are products class
   MazeFactory is the interface between client's code and the concrete factories
   Each concrete factory creates differents sets of products*/
class MazeFactory
{
    public:
        MazeFactory() {/* Implementation */}

        virtual Maze* MakeMaze() const {
            return new Maze();
        }
        virtual Wall* MakeWall() const {
            return new Wall ();
        }
        virtual Room* MakeRoom(int n) const {
            return new Room(n);
        }
        virtual Door* MakeDoor(Room* r1, Room* r2){
            return new Door(r1,r2);
        }
};

// Concrete derived class of MazeFactory
// EnchantedMazeFactory creates EnchantedRoom and DoorNeedSpell
class EnchantedMazeFactory: public MazeFactory
{
    public:
        EnchantedMazeFactory(){/* Implementation */}

        virtual Room* MakeRoom (int n) const {
            return new EnchantedRoom (n);
        }

        virtual Door* MakeDoor (Room* r1, Room* r2){
            return new DoorNeedSpell (r1,r2);
        }

    protected:
        //Spell* CastSpell (void) const;
};


//Concrete subclass of MazeFactory
//BombedMazeFactory creates RoomWithABomb and BombedWall
class BombedMazeFactory: public MazeFactory
{
    public:
        virtual Wall* MakeWall () const {
            return new BombedWall();
        }

        virtual Room* MakeRoom (int n) const {
            return new RoomWithABomb(n);
        }
};

//Maze Game has creatMaze method that creates a Maze object
class MazeGame
{
    public:
      Maze* creatMaze(MazeFactory& factory) // This method can create any type of maze that have MazeFactory class as basic class
      {
          Maze* aMaze = factory.MakeMaze();
          Room* r1 = factory.MakeRoom(1);
          Room* r2 = factory.MakeRoom(2);
          Door* aDoor = factory.MakeDoor(r1,r2);

          aMaze->addRoom(r1);
          aMaze->addRoom(r2);

          r1->SetSide(North, factory.MakeWall());
          r1->SetSide(South, factory.MakeWall());
          r1->SetSide(West, factory.MakeWall());
          r1->SetSide(East,aDoor);

          r2->SetSide(North,factory.MakeWall());
          r2->SetSide(South,factory.MakeWall());
          r2->SetSide(West, aDoor);
          r2->SetSide(East,factory.MakeWall());

          return aMaze;
      }

};


int main()
{
    MazeGame game;
    BombedMazeFactory BombedMaze;
    EnchantedMazeFactory enchantedMaze;

    game.creatMaze(BombedMaze);
    game.creatMaze(enchantedMaze);

    return 0;
}














