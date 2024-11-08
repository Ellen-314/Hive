[Lien](//www.plantuml.com/plantuml/png/xLZ1RXit4BtlLn0-699b1Usb1y4DKXbjKI1stIJerQ1sHp8BBhabkO9TD_cMV4k-h4DEA99UQP46S4uwn5hEl7aat-oGEtbb7JUkRsLLIsujUmlkv_iQEYUqUgpcBLZBDy0MpBfciR3E2BMfgbaEczHQMPS3JbbhDzEgUbzzPhsH_07COrNDQosrGRgLrX9vo36PxfwydGKGsZRWBl4H_IpC4UDcbXmb76VZA-iChnsZQNzJ5chdfrKWDdShRTxf3ad8VfRCI-sSRfEd27Y3J-vmL78FGr_3UYJogPSUQhq5BsBo35GZkrVDWhjEqqq-1p0HVad1t9zqZCY2WfOroaAG8L7YoKGROqgWBrhKADy0DxuyIimOMyACCwKyVi7I3l49U-bJ3itUrvnSYVv_byMirNgBq0NR2kDwBgbIjqYdpGKHB3KtpTjEkxENgMZ_w07K4e3v0c8jlm-d07UYPhsoOgEWOK8vz7NQmb9oLOyYhhKm1m3LZ6t0NV7xjALzE8BTnDaGF0gZAKTG_2_TEp03igqMJN8dakHbw0ww8X6xF_TyxE6SPMgUifN_cVhy6T40nX-KVCO-HB4dqqyVOqXAnK_AFHvpyDmvG9KB-JzzJ1bupPk7LRyvbiBpfY49VgNjtxrm-bifVbHy2U0a7FL-_eE6bDv_rFzgyE-TxZemnrGyVoeokOjyLEzZGzI9vfYARv4AKlffLT27BxluTpxVVP4MHhoryt6ygGjRl4mA8rLXRigBhx3JqcA9xjPD3QqsZL3SWOrTSiU5kK0vpl7Vosek0j6jpt_ssL_D8ernXOJn0tz7Iy8FYJqiTe9bVr961qjg6U-upQAeSUWCCax27Dew0xmzPUlGKLzgvOoMq1jsXaASV7z2sw_2NxATdIH9ecmdtxruWLXqqrD2-Cq0Gz9-2ymYh-IivXRoo1z291aGlzN22ZMWJe3Qand7EbucARGkuIMyjJYrpr1wwNm_llAh4V_0hVC3hBxTE2R8IyOR7x4lJKCp4ZnzktqBreZrmm1CrBIBTthWFcU3fh812Gx8_8lHxP3oK39fLP5XNnobnFmPnBQbDnr9extZR4l1rxsKNqTGBe8s-fLh-R3B7pqK9vDsTs22YuOT68uyF-v3fSlvJI_1KZ-y0lXT1LZwVnacx3AOQUA5DwVWL4gFFfv2QIOSy_LQr3ZR5QW-NW5eRg3bgW4JAbeh1M2ZTt0gi70iLBCGP0oO6swSWCaq7UINt1PZ4fXC3NIIrwNDzbrdH9i7AjLBlvw-2-EqAnpIhIEv0zvdoymrVOfP97j6HH79SCfgP4zfsWjWYzpWhvICqMVn5QYcR-L_)

Code plantuml :
```
@startuml
class SetException{
-message : std::string

+SetException(const std::string& msg)

}

class Player{

-color : bool

+Player()
+Player(bool color)
+getColor() const : bool
+setColor(bool color)
}

abstract class Insect{

-neighborTop : Insect*
-neighborBottom : Insect*
-neighborTopRight : Insect*
-neighborBottomRight : Insect*
-neighborTopLeft : Insect*
-neighborBottomLeft : Insect*
-Insectcovering : Insect*
-color : bool

+Insect()
+setNeighborTop(Insect* insect)
+getNeighborTop() const : Insect* 
+setNeighborBottom(Insect* insect)
+getNeighborBottom() const : Insect*
+setNeighborTopRight(Insect* insect)
+getNeighborTopRight() const : Insect* 
+setNeighborBottomRight(Insect* insect)
+getNeighborBottomRight() const : Insect*
+setNeighborTopLeft(Insect* insect)
+getNeighborTopLeft() const : Insect*
+setNeighborBottomLeft(Insect* insect)
+getNeighborBottomLeft() const : Insect*
+isCovered() const : bool
+setCovered(Insect* i)
+getColor() const : bool
+setColor(bool color)
+moov() : virtual std::vector<const BoardSpot*>
}

class QueenBee {

- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
+ ~QueenBee() override
}

class Ant{
- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
+ ~Ant() override
 
}

class Ladybug{

- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
}

class Mosquito{

- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
}

class Beetle{

- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
+ ~Beetle() override
}

class Grasshopper{

- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
+ ~Grasshopper() override

}
class Spider{

- max : static unsigned int
- poseBlanc : static unsigned int
- poseNoir : static unsigned int

+ getMax() const : static unsigned int
+ getPoseBlanc() : static unsigned int
+ getPoseNoir() : static unsigned int
+ ajouterBlanc() : static void
+ ajouterNoir() : static void 
+ moov(int x, int y, const Board& board)override : vector<const BoardSpot*>
+ ~Spider() override
}

skinparam groupInheritance 2
Insect <|-- QueenBee
Insect <|-- Ant
Insect <|-- Ladybug
Insect <|-- Mosquito
Insect <|-- Beetle
Insect <|-- Grasshopper
Insect <|-- Spider

class BoardSpot{

-coordinates : std::pair<int,int>
-insect_pose : Insect*

+BoardSport(int x, int y)
+getCoordinates() : std::pair<int,int>
+getInsect() : Insect*
+setCoordinates()
+setInsect()
+hasInsect() : bool
+print(std::ostream& f)
}

Controleur *-- "1" Board
Board *-- "*" BoardSpot
Insect "0..1" -- "0..1" BoardSpot : se trouve sur la case
Insect "0..6" -- Insect : voisin
Insect "0..1" -- Insect : couvert par

class Board {

-board_spots : BoardSpot**
-nb : size_t
-nbMax : size_t

+Board()
+addSpot(int x, int y)
+getSpot(int x, int y) : const BoardSpot*
+modifySpot(int x, int y)
+addInsectToSpot(int x, int y, Insect* insect)
+deleteInsectFromSpot(int x, int y)
+print(std::ostream& f) const
+deleteSpot(int x, int y)
+trouverVoisins(int x, int y) const : std::vector<const BoardSpot*>
+voisinsNull(int x, int y) const : std::vector<const BoardSpot*>
+trouverVoisinsInsects(int x, int y) const : std::vector<const BoardSpot*>
+~Board()
+Board(const Board& other)
+Board& operator=(const Board& other)
}

class Rules {

- beeOnBoard : bool

+ isBeeOnBoard():bool
}

class Controleur{
- board : Board
- afficherMenu() const
- demanderCoordonnees() const : std::pair<int, int>

+ demarrerPartie()
+ ajouterCase()
+ ajouterInsecte()
+ deplacerInsecte()
+ supprimerCase()
+ annulerCoup()
+ Controleur()
+ getPlateau() const : const Board&
+ getPlateau() : Board&
+ Controleur(const Controleur& c)
+ operator=(const Controleur& c) : Controleur&
+ ~Controleur()
}
@enduml```
