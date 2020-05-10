<h2>NWP projekt</h2><br>
<h3>Asteroids-like clone za NWP projekt uz korištenje C++, SMFL-2.5.1</h3> 

Otvoriti kroz VS i trebalo bi raditi bez problema, sve potrebno je uključeno u build.

Kod prvog pokretanja igra prpeuzima resoluciju koja je trenutno na desktopu.
U settings-u možete mijenjati rezoluciju, fullscreen(on-default), antialiasing i v_sync.
Također možete prebaciti kontrolu broda na WASD tipke.

Kontrole:<br> 
  &nbsp-strelice(default) ili WASD za kretanje
  &nbsp-space za pucanje
 
Značajke:<br>
  -brod, asteroidi, i enemy imaju "neprekidni ekran", metci ne
  -napredak kroz igru odvija se u levelima, prvi level kreće sa 2 asteroida, i za jedan više u svakom idućem
  -asteroid kod uništenja se raspada na 3 manja(srednja) koji imaju veću brzinu za 50% od prethodnog
  -srednji se raspadaju na 3 mala, mali su zadnji u lancu.
  -kad se unište svi asteroidi prelazi se na idući level, brzine se uvećavaju za 30-ak posto
  -UFO enemy pojavljuje se sa random tajmingom, aktivan je 10 sec., 
   svakim levelom raste mu brzina i kut između linije pucanja se smanjuje
  -Ako se uništi enemy,postoji 30% šansa da dropa ekstra život(aktivan 5 sec.)
  -Kod završetka pojavljuje se high score lista u koju upišete ime ukoliko je rezultat veći od onog
   na 10. mjestu.
  -Povratom na glavni izbornik može se pokrenuti nova igra ili zatvoriti program.
  
  Bodovanje:<br>
    -Asteroid-Veliki-10 bodova
             -Srednji- 20 bodova
             -Mali - 30 bodova
             -Ufo - 40 bodova
             
 Ukoliko bude još nekih promjena u igri biti će navedene ovdije 
