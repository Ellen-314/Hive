[Lien](//www.plantuml.com/plantuml/uml/hLLBRzGm4BxdLrXxG5cMhU2wgb193r2fBKlXldAI8R7asC5seENntvbad8Utx0CfbyJvvfjl7lR4LzPnuvfAHfdarhAjv4zWVaNhJ4jjs8QbMijeHN2y75Ojp3eEOWMuQroY7I5btU1coH3I_qG-resoa3cCfK0KPQhD5rsZAy4lHpZHpkagj0mE3xXoXxr2S-Xw2r-FUEvRC_qT3EI-jlq64IrUTZNVZp5Yxyz4zwPcJUrZotfc846v75KXodCXhnDswgZIG3ehgLDw8UzaUjZlush4EQKqRDuvgHtI4_QQTllV9vfCTARfux-7O5MXOqnkMss54rfDF5rJIuXMMSbL0OEzGvc27xjQsyaWVMe0L0B0S9POnHzHm3hkHCOQPKMX86T2kMZ5CDWTV-pZ7A0Dik-KcrVmbkTFQLFC94gQTzf-QuJJiuec04x2h9Bl3JvBNTTWPjNzN8jyDic89e1T_bwlXrCLW7WcWc-_fG7MRqa0Kai3QDAI0AUIek16-i1LplQlfRNZAQwf9Z-yxNyylR5PLwJu2JiiVvJm4tVVCNmxfipQWCeDR0LaWEPG-qNReKaw6dDTlBwuK0jFy4QsUBDWhGrV8xsl9z7STAMmajjoXoL8sB1Bd_whRiRVufRvEzA1uKwRDZHvFe_gXHyQ2ROJJW4-AcBtFo4cR3AWyNBJegXvXUKsbVmB)

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
