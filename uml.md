[Lien](//www.plantuml.com/plantuml/png/xLZ1RXit4BtlLn0-699b1Usb1y4DKXbjKI1stIJerQ1sHp8BBhabkO9TD_cMV4k-h4DEA99UQP46S4uwn5hEl7aat-oGEtbb7JUkRsLLIsujUmlkv_iQEYUqUgpcBLZBDy0MpBfciR3E2BMfgbaEczHQMPS3JbbhDzEgUbzzPhsH_07COrNDQosrGRgLrX9vo36PxfwydGKGsZRWBl4H_IpC4UDcbXmb76VZA-iChnsZQNzJ5chdfrKWDdShRTxf3ad8VfRCI-sSRfEd27Y3J-vmL78FGr_3UYJogPSUQhq5BsBo35GZkrVDWhjEqqq-1p0HVad1t9zqZCY2WfOroaAG8L7YoKGROqgWBrhKADy0DxuyIimOMyACCwKyVi7I3l49U-bJ3itUrvnSYVv_byMirNgBq0NR2kDwBgbIjqYdpGKHB3KtpTjEkxENgMZ_w07K4e3v0c8jlm-d07UYPhsoOgEWOK8vz7NQmb9oLOyYhhKm1m3LZ6t0NV7xjALzE8BTnDaGF0gZAKTG_2_TEp03igqMJN8dakHbw0ww8X6xF_TyxE6SPMgUifN_cVhy6T40nX-KVCO-HB4dqqyVOqXAnK_AFHvpyDmvG9KB-JzzJ1bupPk7LRyvbiBpfY49VgNjtxrm-bifVbHy2U0a7FL-_eE6bDv_rFzgyE-TxZemnrGyVoeokOjyLEzZGzI9vfYARv4AKlffLT27BxluTpxVVP4MHhoryt6ygGjRl4mA8rLXRigBhx3JqcA9xjPD3QqsZL3SWOrTSiU5kK0vpl7Vosek0j6jpt_ssL_D8ernXOJn0tz7Iy8FYJqiTe9bVr961qjg6U-upQAeSUWCCax27Dew0xmzPUlGKLzgvOoMq1jsXaASV7z2sw_2NxATdIH9ecmdtxruWLXqqrD2-Cq0Gz9-2ymYh-IivXRoo1z291aGlzN22ZMWJe3Qand7EbucARGkuIMyjJYrpr1wwNm_llAh4V_0hVC3hBxTE2R8IyOR7x4lJKCp4ZnzktqBreZrmm1CrBIBTthWFcU3fh812Gx8_8lHxP3oK39fLP5XNnobnFmPnBQbDnr9extZR4l1rxsKNqTGBe8s-fLh-R3B7pqK9vDsTs22YuOT68uyF-v3fSlvJI_1KZ-y0lXT1LZwVnacx3AOQUA5DwVWL4gFFfv2QIOSy_LQr3ZR5QW-NW5eRg3bgW4JAbeh1M2ZTt0gi70iLBCGP0oO6swSWCaq7UINt1PZ4fXC3NIIrwNDzbrdH9i7AjLBlvw-2-EqAnpIhIEv0zvdoymrVOfP97j6HH79SCfgP4zfsWjWYzpWhvICqMVn5QYcR-L_)

Code plantuml :
```
@startuml
class Player{
-color : bool
+Player()
+Player(bool color)
+getColor() const : bool
+setColor(bool color)
}

class Insect{
-neighborTop : Insect*
-neighborBottom : Insect*
-neighborTopRight : Insect*
-neighborBottomRight : Insect*
-neighborTopLeft : Insect*
-neighborBottomLeft : Insect*
-covered : bool
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
+setCovered(bool covered)
+getColor() const : bool
+setColor(bool color)
+move()
+getPosition() const : tuple
+changePosition(tuple new_pos)
}

class QueenBee {
- max : static unsigned int
+ getMax() const : static unsigned int
}

class Ant{
- max : static unsigned int
+ getMax() const : static unsigned int
}

class Ladybug{
- max : static unsigned int
+ getMax() const : static unsigned int
}
class Mosquito{
- max : static unsigned int
+ getMax() const : static unsigned int
}
class Beetle{
- max : static unsigned int
+ getMax() const : static unsigned int
}
class Grasshopper{
- max : static unsigned int
+ getMax() const : static unsigned int
}
class Spider{
- max : static unsigned int
+ getMax() const : static unsigned int
}

Insect <|-- QueenBee
Insect <|-- Ant
Insect <|-- Ladybug
Insect <|-- Mosquito
Insect <|-- Beetle
Insect <|-- Grasshopper
Insect <|-- Spider

class PlayerHand {
-color : bool
-tab : const Insect**
-nbIsct : size_t
+PlayerHand()
+getNbIsct() const : size_t
+prendrePiece() : const Insect&
}

PlayerHand o-- "0..n" Insect
Player "1" -- "1" PlayerHand

class Board {
- hash_table: <Insect*,tuple>
+ class Iterator
}

Board o-- "0..n" Insect

class Rules {
- beeOnBoard : bool
+ isBeeOnBoard():bool
}
@enduml
```
