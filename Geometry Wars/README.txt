1)NUME PRENUME : VIJAEAC CRISTIAN-OCTAVIAN
  GRUPA SERIE : 335CB

2)UTILIZARE APLICATIE:
-Taste: W - miscare in sus
	   A - miscare in stanga
        D - miscare dreapta
        S - miscare in jos
	   
-Mouse: -miscarea mouseului duce la reorientarea 		 	obiectului,intotdeaunca cu fata spre acesta
	   -click stanga pentru a lansa un proiectil/glont

-Stari: -initial playerul se afla in mijlocul ecranului
        -inamicii incep sa apara in jurul lui,pe un cerc 		  	   imaginar,cu viteze random
        -timpul de aparitie scade pana la 0.5 secunde
        -2 inamici : cu 2 vieti si cu o viata
        -cei cu 2 vieti se vor scala la jumatate dupa prima 		   lovitura si isi vor schimba culoare
        -playerul are 3 vieti afisate in dreapta sus
	   -daca playerul ramana fara vieti,scena se blocheaza iar 
	   ecranul va deveni rosu printr-o animatie

3)DETALII DE IMPLEMENTARE:
GameObject - clasa parinte care contine caracteristicile fiecarui 		obiect in parte :pozitie,rotatie,scalare,culoare,etc
Player - clasa care contine caracteristicile playerului
Enemy - clasa care contine caracteristicile fiecarui inamic in 			parte
Bullet - clasa care contine caracteristicile fiecarui glont in 			parte
!Clasele Player,Enemy,Bullet mostenesc clasa parinte GameObject.
Game - clasa care realizeaza toate operatiile si transformarile 	necesare realizarii acestui joc
	-Init() - construieste fereastra logica si viewSpace-ul,initializeaza 	playerul,primul inamic,dreptunghiurile pentru vieti si gloantele
	-AddNewPlayer() - construieste un nou jucator dupa o perioada de timp asa 	cum este mentionat in enunt,seteaza caracteristicile acestuia 
	-CollisionDetected() - verifica daca s-a produs o coliziune player-inamic
       -CollisionBulletDetected() - verifica daca s-a produs o coliziune 
	glont/proiectil - inamic
	-UpdateEnemiesPositions - updateaza pozitia fiecarui inamic la fiecare frame
	precum si indicele de scalare al acestuia in functie de numarul de vieti
	ramase(si culoarea)
	-SetNoLifes() - afiseaza in coltul din dreapta sus numarul de vieti ramase
	sub forma unor dreptunghiuri,in functie de valoarea variabilei "no_lifes"
	-PutPlayerInScene() - updateaza pozitia playerului la fiecare frame
 	-StopGame() - daca playerul ramane fara vieti,fereastra se blocheaza si 
	se porneste o animatie de colorare a ferestrei in rosu
	-TriggerBullet() - updateaza pozitia fiecarui proiectil la fiecare frame
	-Update() - apeleaza functiile de mai sus si updateaza fereastra cu noile 
	informatii obtinute
	-OnInputUpdate() - deplasarea playerului de-a lungul celor 2 axe(sus,jos,
	stanga,dreapta) precum si unghiul de rotatie in functie de pozitia acestuia
	fata de mouse(intotdeauna vectorul directie este indreptat spre mouse)
	-OnMouseMove() - in functie de pozitia mouseului pe ecran se stabileste
	rotatia playerului 
	-OnMouseBtnPress()-un nou proiectil este construit si adaugat in vectorul 
	de proiectile existente deja

4)PROBLEME APARUTE:
-Transformarea fereastra-poarta : din cauza acestui tip de transformare si a faptului ca pozitia mouseului era determinata fata de coltul din stanga sus,a trebuit sa determin o formula matematica pt a afla pozitia mouseului relativa la originea sistemului logic,nu punctului din stanga sus
-Inamicii urmaresc playerului : dificultatea intalnita a constat in faptul ca nu stiam modul in care acest lucru se realizeaza(in unity exista un tip de vectori care fac acest lucru) dar dupa un mic research pe internet mi-am dat seama ca trebuie sa folosesc vectorul normat
-Inamicii se rotesc dupa player : la fel ca mai sus,mi-a luat ceva timp pana mi-am dat seama ca trebuie sa folosesc coordonatele polare pentru acest lucru

5) COTINUTUL ARHIVEI
-

6)STATUS IMPLEMENTARE FUNCTIONALITATI
Toate punctele obligatorii din cadrul acestei teme au fost atinse in proiectul meu.
Nu exista bonus.

			

