<h2>NWP projekt</h2>
<h3>Asteroids-like clone za NWP projekt uz korištenje C++, SMFL-2.5.1</h3> 

Otvoriti kroz VS i trebalo bi raditi bez problema, sve potrebno je uključeno u build.

Kod prvog pokretanja igra postavlja default rezoluciju koja je trenutno na desktopu.
U settings-u možete mijenjati rezoluciju, fullscreen(on-default), antialiasing i v_sync.
Također možete prebaciti kontrolu broda na WASD tipke.

<h4>Kontrole:</h4>
 -strelice(default) ili WASD za kretanje<br>
 -space za pucanje<br>
 <hr>
<h4>Značajke:</h4>
  -brod, asteroidi, i enemy imaju "neprekidni ekran", metci ne<br>
  -napredak kroz igru odvija se u levelima, prvi level kreće sa 2 asteroida, i za jedan više u svakom idućem<br>
  -asteroid kod uništenja se raspada na 3 manja(srednja) koji imaju veću brzinu za 50% od prethodnog<br>
  -srednji se raspadaju na 3 mala, mali su zadnji u lancu.<br>
  -kad se unište svi asteroidi prelazi se na idući level, brzine se uvećavaju za 30-ak posto<br>
  -UFO enemy pojavljuje se sa random tajmingom, aktivan je 10 sec.,
   svakim levelom raste mu brzina i kut između linije pucanja se smanjuje<br>
  -Ako se uništi enemy,postoji 30% šansa da dropa ekstra život(aktivan 5 sec.)<br>
  -Kod završetka pojavljuje se high score lista u koju upišete ime ukoliko je rezultat veći od onog na 10. mjestu.<br>
  -Povratom na glavni izbornik može se pokrenuti nova igra ili zatvoriti program.<br>
  <hr>
  <h4>Bodovanje:</h4>
    -Asteroid-<br>
      -Veliki-10 bodova<br>
      -Srednji- 20 bodova<br>
      -Mali - 30 bodova<br>
    -Ufo - 40 bodova<br>
             <hr>
 Ukoliko bude još nekih promjena u igri biti će navedene ovdije<br> 
