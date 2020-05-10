<h2>NWP projekt</h2><br>
<h3>Asteroids-like clone za NWP projekt uz korištenje C++, SMFL-2.5.1</h3> 

Otvoriti kroz VS i trebalo bi raditi bez problema, sve potrebno je uključeno u build.

Kod prvog pokretanja igra prpeuzima resoluciju koja je trenutno na desktopu.
U settings-u možete mijenjati rezoluciju, fullscreen(on-default), antialiasing i v_sync.
Također možete prebaciti kontrolu broda na WASD tipke.

Kontrole:<br> 
 &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-strelice(default) ili WASD za kretanje<br>
  &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-space za pucanje<br>
 <hr>
Značajke:<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-brod, asteroidi, i enemy imaju "neprekidni ekran", metci ne<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-napredak kroz igru odvija se u levelima, prvi level kreće sa 2 asteroida, i za jedan više u svakom idućem<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-asteroid kod uništenja se raspada na 3 manja(srednja) koji imaju veću brzinu za 50% od prethodnog<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-srednji se raspadaju na 3 mala, mali su zadnji u lancu.<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-kad se unište svi asteroidi prelazi se na idući level, brzine se uvećavaju za 30-ak posto<br>
 &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp; -UFO enemy pojavljuje se sa random tajmingom, aktivan je 10 sec.,
   svakim levelom raste mu brzina i kut između linije pucanja se smanjuje<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Ako se uništi enemy,postoji 30% šansa da dropa ekstra život(aktivan 5 sec.)<br>
  &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Kod završetka pojavljuje se high score lista u koju upišete ime ukoliko je rezultat veći od onog
   na 10. mjestu.<br>
 &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp; -Povratom na glavni izbornik može se pokrenuti nova igra ili zatvoriti program.<br>
  <hr>
  Bodovanje:<br>
    &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Asteroid-<br>
    &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Veliki-10 bodova<br>
    &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Srednji- 20 bodova<br>
             &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Mali - 30 bodova<br>
             &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;-Ufo - 40 bodova<br>
             <hr>
 Ukoliko bude još nekih promjena u igri biti će navedene ovdije<br> 
