# README
Hier ist das Git-Repository von der Gruppe Montag2 (Montag um 10 Uhr, TEL 1015) des Programmierpraktikum
Cyber-Physical Systems.

## Product Backlog
Die Issues, die mit dem Label "product-backlog-item" anlegt werden, beschreiben Funktionen für den Benutzer (wie sie in einem Werbeprospekt aufgeführt würden). Die Backlog Items sollten nicht zu stark voneinander abhängen, sondern in sich abgeschlossen sein, Ausnahmen sind aber möglich. Diese Issues enthalten eine sogenannte User-Story (dazu später mehr), Kriterien zur Fertigstellung und Informationen über die voraussichtlich verwendete Technologie. _Ich habe eine Vorlage für Product Backlog Item-Issues geschrieben, die ihr bei der Issue-Erstellung aus einem Drop-Down-Menü auswählen könnt._

Die Backlog Items werden schließlich priorisiert und mit den Tags der zuständigen Arbeitsgruppen "arduino", "web-frontend" und "backend" gekennzeichnet, um einen Terminplan für das Pflichtenheft zu erstellen. Dabei werden die Backlog Items den Milestones 1-3 zugeordnet.

### User-Story
Eine User Story beschreibt ein Product-Backlog-Item aus der Sicht des Benutzers. Eine gute User-Story beantwortet die Frage, wer welche Funktion wieso benutzt. In der User-Story wird also der Benutzer, die Funktion und die Motivation für ihre Benutzung genannt. Die User-Story erwähnt dabei alle wichtigen Eckpunkte der Funktionen ("Der Benutzer ist in der Lage, die Pflanze auf Wunsch zu Gießen und den Erfolg der Bewässerung später visuell ablesen zu können, damit die Pflanze wächst und nicht vertrocknet.") ohne sich in Details zu verfangen. Die Sprache der User-Story soll einfach aber treffend sein und keine Zweideutigkeiten aufweisen. User-Storys werden im Aktiv verfasst.

## Sprint-Items
Die Einträge des Product Backlogs sind meistens zu groß, um sinnvoll daran arbeiten zu können und dabei den Arbeitsfortschritt zu nachzuverfolgen. Deswegen teilt man sie in Sprint-Items auf. Auch hierfür werden Issues mit dem entsprechenden Label "sprint-item" erstellt. Es gibt auch wieder eine Vorlage, die man benutzen kann.

Ein Sprint-Item verweist in seinem Text auf die Issue-Nummer des zugehörigen Product backlog items und enthält eine kurze Beschreibung der Aufgabe, so dass jeder aus dem durch ein Label markierten Team die Aufgabe übernehmen kann. Die Art der Implementierung wird kurz umrissen.

Die Sprint-Items werden in der Milestone-Phase des zugehörigen Backlog-Items einer Woche zugewiesen, in der sie von den Gruppenmitgliedern, die sich in dem Issue markieren, bearbeitet wird. Wichtige Fortschritte und Rückschläge werden in den Issue-Kommentaren festgehalten.

## Git flow
Wir benutzen ein Commit-Schema namens Git flow, dass der Entwickler Vincent Driessen erstmals 2010 in seinem Blogartikel [A successful git branching model](http://nvie.com/posts/a-successful-git-branching-model/) beschrieb, um unser Projekt zu organisieren. Der Artikel ist eine hilfreiche Einführung in diesen Workflow.

In den Master-Branch kann man also nur durch einen Merge von einem Hotfix- oder Feature-Branch schreiben. Der Master-Branch enthält jederzeit nur stabilen Code. Da ich für die Merges zuständig bin, könnt ihr nicht in den Master-Branch pushen, um Probleme zu vermeiden. Sagt einfach bescheid, wenn ihr einen Branch in Master mergen wollt. Für die Milestones wird es Release-Branches geben.

_Generell solltet ihr immer committen, wenn ihr eine abgeschlossene Einheit Code geschrieben habt und möglichst oft pushen. Denkt aber auch an regelmäßige Pulls, denn die anderen arbeiten (hoffentlich) auch. Eure gepushten Änderungen sollten aber, insbesondere im `develop`-Branch nicht verhindern, dass das Programm kompiliert!
Wenn ihr euch fragt, ob ihr einfach in den `develop`-Branch oder in einen Feature-Branch commiten solltet, so überlegt euch: Ist mein aktuelles Sprint-Item alleinstehend sinnvoll oder ergibt es erst mit anderen Codeänderungen Sinn? Bei ersterem schreibt ihr in `develop`, bei dem letzteren Fall macht ihr einen neuen Feature-Branch auf._

Ihr könnt natürlich `git` auf der Kommandozeile verwenden, es gibt sogar einen Helper für die [Linux und macOS-Konsole](https://danielkummer.github.io/git-flow-cheatsheet/). Für Menschen, die neu bei `git` sind oder auch sonst lieber eine GUI verwenden würden, empfehle ich Atlassins Freeware [SourceTree](https://de.atlassian.com/software/sourcetree) für Windows und macOS. In der Datei source-tree-tutorial.md steht eine Anleitung, wie man das Programm mit dem Repository einrichtet.

## Testen
Ich bin mir sicher, dass Rohan da noch was zu sagen haben wird, aber Merges zu Master sollten eine 90%-Branch-Coverage haben. Die Testfälle von Feature-Branches sollten bei Merge in `develop` schon stehen. Idealerweise schreibt man die Tests vor der Implementierung. Neue Methoden - außer sowas wie der Main - sollten Unit-Tests haben. Die Funktionalität des Gesamtsystems wird mindestens einmal pro Woche im Labor getestet.

## Dokumentation
Alle Methoden werden mit den Dokumentationskommentaren der entsprechenden Sprache gekennzeichnet (Was tut sie, Erklärung von Parametern und Rückgabewerten). In längeren Funktionen sollten Kommentare verwendet werden, damit die anderen die Prozesse nachvollziehen können. Bei Fragen dazu, sprecht mit Daniel.

Wichtige Schnittstellen zwischen z.B. Arduino und Raspberry Pi oder REST-APIs sollten zur besseren Zusammenarbeit in Markdown-Dokumenten im Root des Repositories beschrieben werden.

## Markdown
Dieses schöne Dokument und z.B. alle Issues werden in der Markupsprache Markdown verfasst. Wer damit noch nicht vertraut ist, findet hier ein [Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) und die Beschreibung der [GitLab-spezifischen Funktionen](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md). Für viele Editoren gibt es Syntax-Highlighting oder Vorschau-Pakete.
