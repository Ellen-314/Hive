[Lien](//www.plantuml.com/plantuml/png/xLXDRlCs4Dth58GNWN_i3-sc2oFzyDL1MnH8qZG9kWqeQIApa4ILf0oxQNAMd2Kdwr1ZXc9a2sa0P-L5B6hcpIFrdYXfyaqRhanTv56ISwtP3PYVrmbKHiZo8PeLe3NFWCsPDkbyheqIPHP5apPicCXIcpRWX1Kw6qNHOxHblShv1jH35CqIcKk5TB6KEV9GOZXw7TauQq0Ooy2SuH3pZEROraqq9K8upiPZN01F3ADfVoir9CPEMuB8bh5Kjx924egFVNWXZP55aF45rpWo-wkwQLzw3lSzbM-pD4Za2go8FjDHZU9MDHJYqaytt1OmqHojWc7Uw-YG0GKjgvU585sYWCU9riVaGUzQL1zV5zU_F3AcZyrZ-fcyZ-zOsZu-eS-ivP3klCqfvUd_zxQO55Ak43fdAw5CpNFQgIkaa-gK21QIg_IcacRyrM_QFsg0SW70x0PY1LytJm5kHCBgKekiX1Ilrc2kaXeMEI-JNiIb56eF89gm3Cm5N_jBseKZs9MR3S6zC9go1yN_ahK1rI5RIP7wj2VnMORfHbSaOkifiuVDbBNKF66nFOoiVqgaWFLx9P-m9oVsSFJox4gy5J-Lvk7G7XmzG9K3-L-UlGFdFDt4TNROhN2qmGj-8VNVjJ3oinG_Ahu0C3aSNk_ZWuQKtlse_rNXxr9M5QZ3Mt6qeYLtu4Vqw1gY2a-FLdo25QJqsrr17xxizD_PxFMBD0ZYMxjzxjxKGSozJ88WxS8WrBeRWZWjpMrHjsvbgAELAXKbDw1TcrnneKvHZod-VOrcr1BSsHkWzTqVJJnFeE7s2z_Jal9TOWjphM3Oe8JLJSJtZ4kkVTMsSwWKCWwREQGs2dXnmkwRblfCbaR976h5ngZ4uFi1NN_K_59iFF1UEjq6tttvWbXCqyWZxCK0Gz9w1KmZRyvPmZMqAtzeAhU1kRtVj2Wxr1wGM39bMCL3bvXrABQZEurJMuVyNMSRyjYkHlm3TyQUuFRpvrk3h6GyjHMxREg6aU3jxMrxi5JSRpfWegQhk9MTz9HrkieKSZ10uL-KBBgK-yoaLJc6NNLaYVgp4Li7MVzCwcyU9oiglgpp_6C4uIBeGZ-ubgTN_sWGF9gaMO9oAJojG77a-N4Noh-Th-iSD3N4CS3lPGFp_vXXGYzS62UUsp0MVuCohOlyFm00)

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
