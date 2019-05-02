
enum Direction {North, South, East, West};

/* MapSide is a abstract class that represents all maze objects
*/
class MapSite
{
    public:
       virtual void Enter (void) = 0;
};


/* Room is a concrete subclass of Mapside that represents maze's rooms
*/
class Room: public MapSite
{
    public:
        Room (int roomNumber);

        MapSite* GetInside (Direction) const;
        void SetSide (Direction, MapSite* );

        virtual void Enter (void);

    private:
        MapSite* _sides[4];
        int _roomNumber;
};

/* Wall is a concrete subclass of Abstract MapSide class that represents maze's wall
*/
class Wall: public MapSite
{
    public:
        Wall();

        virtual void Enter ();
};

/* Door is a concrete subclass of Abstract MapSide class that represent a door between maze's room
*/
class Door: public MapSide
{
    public:
        Door (Room* = 0, Room* = 0);

        virtual void Enter();
        Room* OtherSideFrom(Room*);

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
        Maze();

        void addRoom(Room*);
        Room* RoomNo (int) const;

    private:
        /* private attributes*/

};

/* Room, Door and Wall are products class
   MazeFactory is the interface between client's code and the concrete factories
   Each concrete factory creates differents sets of products*/
class MazeFactory
{
    public:
        MazeFactory();

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

// Concrete subclass of MazeFactory
class EnchantedMazeFactory: public MazeFactory
{
    public:
        EnchantedMazeFactory();

        virtual Room* MakeRoom (int n) const {
            return new EnchantedRoom (int n);
        }

        virtual Door* MakeDoor (Room* r1, Room* r2){
            return new DoorNeedingSpeel (r1,r2);
        }

    protected:
        Spell* CastSpell (void) const;
};


//Concrete subclass of MazeFactory
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


class MazeGame
{
    public:
      Maze* creatMaze(MazeFactory& factory)
      {
          Maze* aMaze = factory.MakeMaze();
          Room* r1 = factory.MakeDoor(1);
          Room* r2 = factory.MakeDoor(2);
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














