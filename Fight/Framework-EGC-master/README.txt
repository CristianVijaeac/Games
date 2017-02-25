1)NUME PRENUME : VIJAEAC CRISTIAN-OCTAVIAN
  GRUPA SERIE : 335CB

2)UTILIZARE APLICATIE:
-Taste: 
Player1:W - aparare
	   A - miscare in stanga
        D - miscare dreapta
        S - lovitura cu pumnul
	  SPACE - lovitura cu piciorul

Player1:UP - aparare
	   LEFT - miscare in stanga
        RIGHT - miscare dreapta
        DOWN - lovitura cu pumnul
	  NUM0 - lovitura cu piciorul
	   
-Stari: -initial playerii se afla la o distanta unul fata de 		celalalt si se afla in starea de "stat" unde nu s-a executat
	nicio actiune de catre niciunul
	-jucatorii pot executa una din actiunile de miscare,lovitura
	cu pumnul sau piciorul si de barare lovituri
	-in cazul mersului se modifica pozitia "patratului" iar apoi
	se randeaza urmatoarea animatie(Care se schimba dupa un 	anumit timp) - schimbarea animatiei se accelereaza cu cat
	tinem mai mult apasat pe tasta
	-in cazul loviturii cu pumnul se incearca verificarea daca 
	lovitura poate cauza o coliziune(daca playerii sunt spate
	in spate acest lucru nu se poate intampla,etc) iar apoi
	se verifica daca s-a produs coliziune in functie de 
	distanta dintre cei 2 playeri
	-daca playerul ce pare a fi lovit bareaza aceasta lovitura
	atunci ea nu se ia in considerare
	-daca o coliziune s-a produs se trece la animatie de
	prabusire a jucatorului lovit
	-acestuia i se ia un nr de vieti(din cele 10) in functie de
	tipul loviturii:pumn-1 viata,picior-3 vieti
	-daca un player ramane fara viata,atunci el va cicla prin
	animatia de prabusire iar celalalt player prin cea de 	castigare
	-jocul se desfasura pana cand un player ramane fara vieti
	-de asemenea,am avut grija ca cei 2 playeri sa nu poate iesi
	din ecran iar bararea de lovituri sa se poate face 	continuu,fara intreruperi        

3)DETALII DE IMPLEMENTARE:
Player - clasa care contine caracteristicile playerului precum 
	  si functiile necesare determinarii noilor coordonate de
	  textura
	  -in cadrul ei exista mai multe metode(cate una pt fiecare
	  tip de animatie posibil) care calculeaza coordonatele
	  urmatoarei texturi ce urmeaza a fi afisata si 	  		reinitializeaza anumite variabile
	  -tot aici se calculeaza noile coordonate in cadrul unui
	  miscari pe orizonatale
SpriteSheet-clasa care parseaza fisierul auxiliar
		-aceasta se foloseste de un utilitar numit PUGIXML
		cu ajutorul caruia,pentru fiecare sprite si deduce
		punctul de inceput,latimea si inaltimea acestuia
		-toate aceste date sunt puse in niste vectori
		in functie de animatie pe care o reprezinta
Game - clasa care realizeaza toate operatiile si transformarile 	necesare realizarii acestui joc

	-Init() - initializeaza 	playerul,camera,meshele,primele
	coordonate de textura si vectorii cu coordonatele animatiei

	-CheckCollision ->metoda care verifica da o lovitura
	poate cauza o coliziune;in caz afirmativ,se verifica daca
	lovitura chiar a produs o coliziune cu celalalt player
				-daca o coliziune este detectata atunci
	se scade din nr de vieti al inamicului lovit si se marcheaza
	faptul ca acesta este lovit

	-runStayAnimationP1() - in cazul in care playerul 1 nu face 
	nicio actiune atunci se considera ca el sta si astfel daca
	a trecut un timp de la ultima animatie,se calculeaza 
	urmatoarea animatie de "stat"

	-runStayAnimationP2() - in cazul in care playerul 2 nu face 
	nicio actiune atunci se considera ca el sta si astfel daca
	a trecut un timp de la ultima animatie,se calculeaza 
	urmatoarea animatie de "stat"

	-player1Wins() - metoda care detecteaza faptul ca playerul 1
	l-a lovit pe playerul 2 si automat va face o animatie 	specifica de castig(in cazul in care playerul 2 nu mai are 	vieti si moare) sau de stat marcand sf loviturii si 	asteptand ridicarea inamicului(in cazul in care playerul 
	2 mai are vieti)
	
	-player2Wins() - metoda care detecteaza faptul ca playerul 2
	l-a lovit pe playerul 1 si automat va face o animatie 	specifica de castig(in cazul in care playerul 1 nu mai are 	vieti si moare) sau de stat marcand sf loviturii si 	asteptand ridicarea inamicului(in cazul in care playerul 
	1 mai are vieti)

	-Update() - apeleaza functiile de mai sus si updateaza fereastra cu noile informatii obtinute
			-daca niciun player nu a fost lovit se verifica
			coliziunile
			-daca nu exista nicio coliziune se verifica daca
			playerii stau sau s-a intreprins o actiune(in 
			cadrul OnInputUpdate())
			-daca unul din playeri a fost lovit se apeleaza
			una din functiile de mai sus

	-OnInputUpdate() - in cadrul functie,pt cei 2 playeri se 					verifica:
				-daca unul din ei se misca pe orizontala
				si timpul necesar executarii unei noi 
				animatii de miscare a trecut,atunci
				se cauta urmatoarea animatie de acest
				timp din vector
				-daca unul din ei executa o miscare de
				lovitura(pumn sau picior) se marcheaza 					acest lucru printr-o variabila hit urmand 					ca la	urmatorul frame sa se faca updateul
				animatiei
				-daca unul din ei se apara atunci se 						marcheaza acest lucru printr o variabila
				si apoi se executa urmatoarea animatie
				de acest tip


4)PROBLEME APARUTE:
-Dificultati din cauza modului in care am facut detectarea sprite-urilor(nu pe coordonate u si v ci pe puncte latime si inaltime).Acest lucru mi-a creat o dificultate in intelegerea modului in care textura este randata si coordonatele sunte setate.
-Daca randam cei 2 playeri,primul se randa pe jumatate si al doilea bine.Daca scoatem unul din ei,celalalta se randa bine.Acest lucru se datora unor modificari aduse in RenderMesh.
-Probleme in momentul in care un player lovea iar celalalt se apara.Din cauza timpului mare de schimbare a animatie nu se detecta miscarea defensiva si astfel playerul era lovit.Acest lucru s-a rezolvat prin introducerea unei noi variabile.
-Problema la collapse:in momentul in care playerul lovit pica,acesta apare deformat din cauza interpolarii gresite.Nu am stiut cum sa rezolv aceasta problema asa ca am lasat asa.

5) COTINUTUL ARHIVEI
-

6)STATUS IMPLEMENTARE FUNCTIONALITATI
Toate punctele obligatorii din cadrul acestei teme au fost atinse in proiectul meu.
Nu am atins niciun bonus din cele mentionate in tema dar ca actualizari am inclus o noua miscare(lovitura cu piciorul,animatie de castig) si am introdus sistemul de vieti.De asemenea am adaugat un background.

			


