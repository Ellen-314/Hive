[Lien](https://www.plantuml.com/plantuml/svg/xLZDRXit4BxlKx0-62klRRGzz20uHYgZBGp4hfi4lHhKxbXYkqjk-IFOTPrdoRMlaRvOXpkXkDHAYoI0SzB14ZdppJV36Vve_D9OhgrhwgoikJ7i3TYVxajehL3oCJjfm1Y-03PbnbRJgR5Qo4MM5NrONYffR1zmo1gpc6JPK_QHzQRc3w0Vi-oaLBNII3TNgaOUKkIJzSZBMGT2sGBi1GvHppeVmQumf4ZXw8tFZTMyj8pSNae3fVLk9OZ5SgxqMzKY2ScFedYch5LDeea6ht5aTrkbwjJq5ToDM6vgQL2g5VWaHiqWQoJtMJDWhwEx_AC14zstps2gZtaCIA98mXfb8SYGAE49IHjb2g1F2sgCRuWR3uyACyv6c16cj8wV4jekFc4kVCcXshhDIHNfF_jO58rIAuHEsKfewtXD9tM5T4gV4S5CSLszQPKzEe-7zZS786S0p1yWrl3xxXRWLfJCIICM4Yecf4LTgmpCQYxBKSIr4de782iOBkgAtuSbRSSHx2PuG_0eZ5oEeFWVobdG0xAL4bLKfoIaPQZkyef4xFwO-Q-7OzRBvY6R-w-9hvyM5Q3zpfGNx5r8TZxvy3wOn5ByAEtZSzTWNmFCSfB-3-zZ1Lxnwc7k5izx5FPbY0c_KkOl9wpwMXdVPtm6O6ju_dplBnhAzFQh_XUDdqlLjg2VlnJxKlJIdTGZUmeDKIkghr6AVIaeqvkdmlmfPCirRzX2AzTUoYLeOJ5QODzdzAkOdVrpShB-kPe8yKdlpyCpdiZ2IvC8wOWcejvMIUGKTpY_wqLHjwjq9IItO48BtNAXpuIqn_XtdfrGkt3hDqUl9yYAGADjaj_mwtzDcq-s4tjOQ1FJvYMrxYIndrno4oRhhgBLo9XtFfIn6dXpoEwwTlj2IQjL3Kwp8qp4mNS7jFoi-oJPqK5CIKZRmRUdfuX5DOqYmYy669Aw5J23l3Ld9JVGj_oXioI1tr9A625JwWHGUZ9jMSlJ8dLzJRT3RmswzXMAEz8twtCVZVWRRgsVuD5SpqE1VCfuvIssbMaeHeBDhU_xiqhSFGp0H4shUAi6wcCsw3WhgC42YN_MgXbIxYecHHKOjjbHIVJlNR9DgettrMXZMQp8-DhLzPSHf47GGhymbdVh-j4WkRQKNO96LPYse3dolDYEOdDO21clRT9VMZ92FSXgfpQy-wcOMkv4bFVs9ZCJL9TEQv1sOzjcnJhUeiWdcmuFU_gZD2gYw0E-UP6dOGcR_il1XvyYJa_FYGiHpefQcF_-xP-yrwu6GykR0_mg2KjiFdPXPcjnFfa69sGSxvj7Rq-cv0xd_EvEb5YIAv0kh0p55JHSLg2xQqz92M22Td1rikxkp8hEI6lGDrnR0VaaFeKNt2HpseKagg2jUPdAZ6jRBPg-ePIkzl6ujfl7LU6KtksQM-0kXfcygfkOQP0dL6GH1OUiHFR1Nau1RDeN-4Sv2UufUmcoSatzFm00)

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
+ begin() const : BoardIterator
+ end() const : BoardIterator
}

class BoardIterator {

- BoardIterator(BoardSpot** s)
- current : BoardSpot**

+ operator++() : BoardIterator&
+ operator*() const : BoardSpot&
+ operator!=(BoardIterator it) const : bool
}

BoardIterator ..> Board : utilisé par

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
@enduml
```
