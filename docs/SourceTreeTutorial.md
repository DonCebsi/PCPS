# Einrichtung von Source Tree mit git flow
Dieses Tutorial ist auf Windows geschrieben. Auf macOS sollten die Schritte sehr ähnlich sein.

1. Zuerst wählt ihr in der Menüleiste `Clone`. Ihr gebt den Repository-Link https://username@gitlab.tubit.tu-berlin.de/username/pcps.git in das Repository-Feld ein und wählt einen lokalen Pfad, an dem ihr eure Dateien ablegen wollt.   
   ![Klonen Fenster mit den Anmeldedaten](http://mha.ug/images/clone-ink.jpg) 
2. Ihr werdet nun von eurem Betriebssystem aufgefordert, euer Tubit-Passwort einzugeben - dieses Fenster war bei mir zuerst nicht im Vordergrund, also sucht u.U. in der Taskleiste! Wenn ihr euch eingeloggt habt, könnt ihr auf `Klonen` drücken.   
   ![Windows-Sicherheitsprompt](http://mha.ug/images/security.png)
3. Nun wäre ein guter Zeitpunkt, um die Identität, mit der ihr committed, festzulegen. Dazu geht ihr in das Menü `Tools` > `Optionen` und ändert Standardbenutzernamen und E-Mail auf eure Campus Mail und euren vollen Namen, den ihr auf der TU hinterlegt habt. Nur so werden eure Commits euch auf GitLab auch zugeordnet.  
   ![Einstellungs-Dialog](http://mha.ug/images/preferences-ink.jpg)
4. Zuerst solltet ihr in der Seitenleiste `Remote` ausklappen und durch einen Doppelklick alle verbleibenden Branches (außer `HEAD`) auschecken. Nun wählt ihr in der Symbolleiste Git Flow aus und bestätigt die Standardwerte in dem Fenster. Jetzt könnt ihr mit dem Knopf einfach neue Feature-, Hotfix- und Release-Branches anfangen. Danach wäre ein guter Augenblick, um euren Branch durch Doppelklick auf `develop` in der Seitenleiste umzustellen. Bei einem Branch-Wechsel darf es keine nicht-committeten Änderungen geben.  
   ![Git Flow Setup-Dialog](http://mha.ug/images/git-flow-ink.jpg)  
   Bei einem Klick auf `Commit` kann man nun eine Übersicht über die eigenen lokalen Änderungen sehen und sie mit einer aussagekräftigen Nachricht comitten. Mit `Pull` werden die Änderungen auf dem aktuellen Branch von GitLab abgeholt.
5. Wenn ihr nun lokal Commits gemacht habt, könnt ihr sie nun mit einem Klick auf `Push` auf den Server hochladen. Wählt dazu nur die Branches aus, die ihr tatsächlich verändert habt und merkt, dass ihr nicht auf Master schreiben könnt.  
   ![Push Dialog](http://mha.ug/images/push-ink.jpg)
