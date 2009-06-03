#!/usr/bin/env tclsh
# French (fran�ais) translations for PureData
# $Id: francais.tcl,v 1.1.2.5.2.8 2007-07-11 19:21:32 matju Exp $
# by Patrice Colet

say file "Fichier"
  say new_file "Nouveau Fichier"
  say open_file "Ouvrir Fichier..."
  say server_prefs "Pr�f�rences serveur..."
  say client_prefs "Pr�f�rences client..."
  say send_message "Envoyer message..."
  say paths "Chemins..."
  say close "Fermer"
  say save "Sauvegarder"
  say save_as "Sauvegarder sous..."
  say print "Imprimer..."
  say quit "Quitter"
  
  say canvasnew_file "Nouveau Fichier"
  say canvasopen_file "Ouvrir Fichier..."
  say canvassave "Sauver"
  say canvassave_as "Sauver sous..."
  #say clientpdrc_editor "�diteur de .pdrc"
  #say clientddrc_editor "�diteur de .ddrc"
  say canvasclose "Fermer"
  say canvasquit "Quitter"
  
say edit "�dition"
  say undo "D�faire"
  say redo "Refaire"
  say cut "Couper"
  say copy "Copier"
  say paste "Coller"
  say duplicate "Dupliquer"
  say select_all "S�lectionner tout"
  say text_editor "�diteur de texte..."
  say font "Police"
  say tidy_up "Aligner"
  say edit_mode "Mode d'�dition"
  say editmodeswitch "Mode �dition/execution"
  
  say canvascut "Couper"
  say canvascopy "Copier"
  say canvasundo "Annuler"
  say canvasredo "R�tablir"
  say canvaspaste "Coller"
  say canvasduplicate "Dupliquer"
  say canvasselect_all "S�lectionner Tout"
  say canvaseditmodeswitch "Mode �dition/execution"
  
say view "Vue"
  say reload "Recharger"
  say redraw "Redessiner"
  
  say canvasreload "Recharger"
  say canvasredraw "Redessiner"
  
  say find "Trouver"
  say find_again "Trouver encore"
  say find_last_error "Trouver la derni�re erreur"
   say string "Trouver cha�ne de charact�res"
 say canvasfind "Trouver"
  say canvasfind_again "Trouver encore"

say put "Mettre"
  say Object "Objet"
  say Message "Message"
  say Number "Nombre"
  say Symbol "Symbole"
  say Comment "Commentaire"
  say Array "Tableau"

say media "M�dia"
  say audio_on "Audio ON"
  say audio_off "Audio OFF"
  say test_audio_and_midi "Tester l'audio et le MIDI"
  say load_meter "CPU-m�tre"
  
  say canvasaudio_on "Audio ON"
  say canvasaudio_off "Audio OFF"
  say clienttest_audio_and_midi "Tester l'audio et le MIDI"
  say canvasload_meter "CPU-m�tre"

say window "Fen�tre"

say help "Aide"
  say about "� propos de..."
  say pure_documentation "Pure Documentation..."
  say class_browser "Explorateur de classes..."

  say canvasabout "� propos de..."
  
  say properties "Propri�t�s"
say open "Ouvrir"

### for key binding editor
say general "G�nerale"
say audio_settings "Param�tres audio"
say midi_settings "Param�tres MIDI"
say latency_meter "Latence-m�tre"
say Pdwindow "Console PD"

say canvaspdwindow "Console PD"
say canvaslatency_meter "Latence-m�tre"
say clientaudio_settings "Param�tres audio"
say clientmidi_settings "Param�tres audio"

### for Properties Dialog (phase 5B)
say_category IEM
say w "Largeur(px)"
say h "Hauteur(px)"
say hold "Temps de maintien(ms)"
say break "temps d'arr�t(ms)"
say min "Valeur minimum"
say max "Valeur maximum"
say is_log "Mode"
say linear "Lineaire"
say logarithmic "Logarithmique"
say isa "Initialisation"
say n "Nombre de choix"
say steady "R�gularit�"
say steady_no  "Caler sur le clic"
say steady_yes "Suivre le clic"
say snd "symbole d'envoi"
say rcv "symbole de reception"
say lab "�tiquette"
say ldx "D�calage x de l'�tiquette"
say ldy "D�calage y de l'�tiquette"
say fstyle "Style de police"
say fs "Taille de la police"
say bcol "Couleur d'arri�re plan"
say fcol "Couleur du premier plan"
say lcol "couleur de l'�tiquette"
say yes "Oui"
say no "Non"
say courier "courrier (typewriter)"
say helvetica "helvetique (sansserif)"
say times "times (serif)"
say coords "Afficher sur le parent"

say_category "Propri�t�s du Gatom"
say width "Largeur"
say lo "Plus Petite Limite"
say hi "Plus Grande Limite"
say label "�tiquette"
say wherelabel "O� montrer l'�tiquette"
say symto "Symbole d'envoi"
say symfrom "Symbole de reception"

say_category "Propri�t�s du graphe"
say x1   "Depuis x"
say x2   "Vers x"
say xpix "Largeur d'�cran"
say y2   "Depuis y"
say y1   "Vers y"
say ypix "Hauteur d'�cran"

say_category "Propri�t�s du canevas"
#say xscale "X units/px"
#say yscale "Y units/px"
say gop "Afficher sur le parent"
say xmargin "Marge x"
say ymargin "Marge y"
say height "Hauteur"
say_category MainWindow
say name "Nom"
say n    "Taille"
say xfrom "�tendue sur x depuis"
say xto "�tendue sur x jusque"
say yfrom "�tendue sur y depuis"
say yto "�tendue sur x jusque"


### Main Window

say in "entr�e"
say out "sortie"
say audio "Audio"
say meters "Niveaux"
say io_errors "Erreurs d'E/S"
say cannot "ne peut"

say_category Autre
say_namespace summary {
  say_category IEMGUI
#  say bng    "D�clencheur"
  say bng    "Bang"
  say tgl    "Interrupteur"
  say nbx    "Boite de Nombre (IEM)"
# say Number2 "Nombre2"
  say hsl    "Glissi�re (Horizontale)"
  say vsl    "Glissi�re (Verticale)"
# say hsl    "S�lecteur (Horizontal)"
  say hradio "Bo�te De Selection (Horizontale)"
  say vradio "Bo�te De Selection (Verticale)"
#  say cnv    "Illustration (IEM)"
  say cnv    "Canevas (IEM)"
  say dropper "Boite Pour Glisser-D�poser"
  say vu     "Vu-m�tre"

  say_category GLUE
  say bang "Envoyer un D�clenchement"
  say float "Stocker et rapeller un nombre flottant"
  say symbol "Stocker et rapeller un symbole"
  say int "Stocker et rapeller un nombre entier"
  say send "Envoyer un message vers un objet d�fini"
  say receive "Recevoir un message envoy�"
  say select "Tester la reception d'un chiffre ou d'un symbole"
  say route "Diriger un message en fonction du premier �lement"
  say pack "Empaqueter un message"
  say unpack "D�sempaqueter un message"
  say trigger "Mettre en s�quence un message"
  say spigot "Interrupteur de message"
  say moses "partitionner un flot num�rique en deux (mo�se)"
  say until "M�chanisme de bouclage"
  say print "Afficher un message dans la console"
  say makefilename "Formater un symbole avec un champ variable"
  say change "Supprimer les r�petitions d'un flot"
  say swap "Permuter deux chiffres"
  say value "Partager une valeur num�rique"

  say_category TEMPS
  say delay "Envoyer un d�clenchement apr�s un d�lai"
  say metro "Envoyer un d�clenchement p�riodiquement"
  say line "Envoyer lin�airement une serie de nombres "
  say timer "Mesurer l'intervalle de temps"
  say cputime "Mesurer le temps de calcul"
  say realtime "Mesurer le temps r�el"
  say pipe "D�lai dynamique pour les nombres"

  say_category MATH
  say + "Ajouter"
  say - "Soustraire"
  say * "Multiplier"
  say {/ div} "Diviser"
  say {% mod} "Retenue d'une Division"
  say pow "Exponentiel"
  say == "�gal?"
  say != "Different?"
  say > "Plus Grand Que?"
  say < "Plus Petit Que?"
  say >= "Plus Grand ou �gal �?"
  say <= "Plus Petit ou �gal �?"
  say &  "et logique (and)"
  say |  "ou logique (or)"
  say && "et logique (and)"
  say || "ou logique (or)"
  say mtof "MIDI vers Hertz"
  say ftom "Hertz vers MIDI"
  say powtodb "Watts vers dB"
  say dbtopow "dB vers Watts"
  say rmstodb "Volts vers dB"
  say dbtorms "dB vers Volts"
  say {sin cos tan atan atan2 sqrt} "Trigonometrie"
  say log "Logarithme d'Euler"
  say exp "Exponentiel d'Euler"
  say abs "Valeur absolue"
  say random "Al�atoire"
  say max "Le plus grand des deux nombres"
  say min "Le plus petit des deux nombres"
  say clip "Forcer un nombre entre deux valeurs"

  say_category MIDI
  say {notein ctlin pgmin bendin touchin polytouchin midiin sysexin} "Entr�e MIDI"
  say {noteout ctlout pgmout bendout touchout polytouchout midiout}  "Sortie MIDI"
  say makenote "Programmer un message d�cal� \"note off\" correspondant � un note-on"
  say stripnote "ignorer les messages \"note off\" "

  say_category TABLEAUX
  say tabread "Lire Un Nombre Depuis Une Tableau"
  say tabread4 "Lire Un Nombre Depuis Une Tableau, avec 4 points d'interpolation"
  say tabwrite "Ecrire un nombre dans une tableau"
  say soundfiler "Lire et �crire un tableau vers un fichier"

  say_category MISC
  say loadbang "D�clencher au lancement"
  say serial "Contr�le du port serie pour NT seulement"
  say netsend "Envoyer messages � travers internet"
  say netreceive "Recevoir messages � travers internet"
  say qlist "S�quenceur de messages"
  say textfile "Convertisseur de fichier vers messages"
  say openpanel "dialogue \"Ouvrir\" "
  say savepanel " dialogue \"Sauver sous\""
  say bag "S�rie de nombres"
  say poly "Allocation de voix polyphoniques"
  say {key keyup} "Valeurs Num�riques Du Clavier"
  say keyname "Nom symbolique d'une touche de clavier"

  say_category "AUDIO MATH"
  foreach word {+ - * /} {say $word~ "[say $word] (for signals)"}
  say max~ "Valeur maximale de signaux"
  say min~  "Valeur minimale de signaux"
  say clip~ "Contraint le signal � rester entre deux valeurs"
  say q8_rsqrt~ "Racine carr�e r�ciproque (attention -- 8 bits!)"
  say q8_sqrt~ "Racine carr�e (attention -- 8 bits!)"
  say wrap~ "Envelopper autour (Genre De partie fractionnelle)"
  say fft~ "Transformation discr�te de Fourier"
  say ifft~ "Partie complexe de la transform�e de fourier"
  say rfft~ "Partie r�elle de la transform�e de fourier"
  say rifft~ "Inverse de la Partie r�elle de la transform�e de fourier"
  say framp~ "Donne la rampe pour chaque block"
  foreach word {mtof ftom rmstodb dbtorms rmstopow powtorms} {
    say $word~ "[say $word] (pour les signaux)"
  }
}

### phase 3

say_namespace summary {
  say_category "AUDIO GLUE"
  say dac~ "Sortie audio"
  say adc~ "Entr�e audio"
  say sig~ "Conversion d'un nombre vers un signal"
  say line~ "G�n�re une rampe audio"
  say vline~ "line~ de luxe"
  say threshold~  "D�tecte les seuils d'un signal"
  say snapshot~ "�chantillonne un signal (converti en nombres)"
  say vsnapshot~ "snapshot~ de luxe"
  say bang~ "Envoie un signal de d�clenchement apr�s chaque block DSP"
  say samplerate~ "Obtient la fr�quence d'�chantillonnage"
  say send~ "Connection d'un signal non-local avec un transcepteur" #fanout=transceiver=transcepteur
  say receive~ "Re�oit le signal venant de send~"
  say throw~  "Additionne le Signal � un bus" 
  say catch~ "D�finit et lit la somme des signaux dans un bus"
  say block~ "sp�cifie la taille et la convergence d'un block"
  say switch~ "Permutation marche/arr�t du calcul DSP"
  say readsf~ "Lit un fichier audio depuis le disque"
  say writesf~ "Enregistre un fichier audio sur le disque"

  say_category "OSCILLATEURS AUDIO ET TABLEAUX"
  say phasor~ "Oscillateur en Dent De Scie"
  say {cos~ osc~} "oscillateur cosinuso�dal"
  say tabwrite~ "�crit dans un tableau"
  say tabplay~ "Lecture d'un tableau (non-transpositeur)"
  say tabread~ "Lecture non-interpolatrice d'un tableau"
  say tabread4~ "Lecture d'un tableau avec quatre points d'interpolation"
  say tabosc4~ "Oscillateur � table d'onde"
  say tabsend~ "�crit continuellement un block dans un tableau"
  say tabreceive~ "Lit continuellement un block dans un tableau"

  say_category "FILTRES AUDIO"
  say vcf~ "filtre contr�l� par un signal (voltage)"
  say noise~ "g�n�rateur de bruit blanc"
  say env~ "suiveur d'enveloppe"
  say hip~ "filtre passe haut"
  say lop~ "filtre passe bas"
  say bp~ "filtre passe bande"
  say biquad~ "filtre brut"
  say samphold~ "�chantillonneur bloqueur"
  say print~ "imprime un ou plusieurs \"blocks\""
  say rpole~ "filtre � valeurs r�elles brut un-p�le"
  say rzero~ "filtre � valeurs r�elles brut z�ro-p�le"
  say rzero_rev~ "[say rzero~] (temps-invers�)"
  say cpole~ "[say rpole~] (valeurs-complexes)"
  say czero~ "[say rzero~] (valeurs-complexes)"
  say czero_rev~ "[say rzero_rev~] (valeurs-complexes)"

  say_category "DELAI AUDIO"
  say delwrite~ "�crit dans une ligne de delai"
  say delread~ "lit depuis une ligne de delai"
  say vd~ "lit depuis une ligne de delai � un temps de delai variable"

  say_category "SUBWINDOWS"
  say pd "Definie un subwindow"
  say table "Tableau de nombres dans une sous-fen�tre"
  say inlet "Ajouter une entr�e � une abstraction ou sous-patch"
  say outlet "Ajouter une sortie � une abstraction ou sous-patch"
  say  inlet~  "[say inlet] (pour un signal)"
  say outlet~ "[say outlet] (pour un  signal)"

  say_category "CALIBRAGE DE DONNEES"
  say struct "d�finit une structure de donn�es"
  say {drawcurve filledcurve} "Dessine une courbe"
  say {drawpolygon filledpolygon} "Dessine un polygone"
  say plot "parcelle le champ d'un tableau"
  say drawnumber "Imprime une valeur num�rique"

  say_category "ACCEDER AUX DONNEES"
  say pointer "Pointe vers un objet appartenant � un calibrage"
  say get "Obtient des champs num�riques"
  say set "Change des champs num�riques"
  say element "Obtient l'�l�ment d'un tableau"
  say getsize "Obtient la taille d'un tableau"
  say setsize "Change la taille d'un tableau"
  say append "Ajoute un �l�ment � la liste"
  say sublist "Obtient un pointeur dans la liste qui est l'�l�ment d'un autre scalaire"
  say scalar "Dessine un scalaire sur le parent"
  
  say_category "OBSOLETE"
  say scope~ "(utiliser tabwrite~)"
  say namecanvas "Donne un symbole de r�ception au canevas contenant cet objet" ;# what was this anyway?
  say template "(utiliser struct)"
}

# phase 4 (pdrc & ddrc)

say section_audio "Audio"
  say -r "Fr�quence d'�chantillonage"
  say -audioindev "Appareils audio en entr�e"
  say -audiooutdev "Appareils audio en sortie"
  say -inchannels "Nombre de canaux d'entr�e audio(par appareil, comme \"2\" ou \"16,8\")"
  say -outchannels "Nombre de canaux de sortie audio (pareil)"
  say -audiobuf "specifie la taille de la m�moire tampon en msec"
  say -blocksize "specifie la taille du block audio I/O en nombre d'�chantillons"
  say -sleepgrain "specify number of milliseconds to sleep when idle"
  say -nodac "Supprime la sortie audio"
  say -noadc "Supprime l'entr�e audio"
  say audio_api_choice "Audio API"
    say default "default"
    say -alsa "use ALSA audio API"
    say -jack "use JACK audio API"
    say -mmio "use MMIO audio API (default for Windows)"
    say -portaudio "use ASIO audio driver (via Portaudio)"
    say -oss "use OSS audio API"
  say -32bit "allow 32 bit OSS audio (for RME Hammerfall)"
  say {} "default"

say section_midi "MIDI"
  say -nomidiin "Supprime l'entr�e MIDI"
  say -nomidiout "Supprime la sortie MIDI"
  say -midiindev  "Liste des appareils MIDI en entr�e; e.g., \"1,3\" pour le premier, et le troisi�me"
  say -midioutdev "Liste des appareils MIDI en sortie, m�me format"

say section_externals "Externals"
  say -path     "Chemin de recherche de fichiers"
  say -helppath "Chemin de recherche des fichiers d'aides"
  say -lib      "Charge une librairie d'objets"

say section_gui "Gooey"
  say -nogui "supprime le d�marrage du GUI (attention)"
  say -guicmd "substitue le GUI � un autre programme (e.g., rsh)"
  say -console "console scrollback lines (0 = disable console)"
  say -look "ic�ne de la barre des boutons"
  say -statusbar "active la barre de status"
  say -font "Specifie la taille par d�faut de la police"

say section_other "Autre"
  say -open "ouvrir un ou plusieurs fichier(s) au d�marrage"
  say -verbose "extra printout on startup and when searching for files"
  say -d "debug level"
  say -noloadbang "disable the effect of \[loadbang\]"
  say -send "envoie un message au d�marrage (apr�s que les patches soient charg�s)"
  say -listdev "list audio and MIDI devices upon startup"
  say -realtime "use real-time priority (needs root privilege)"

say section_paths "Paths"

# phase 4B: ddrc (keyword names not finalized!)

say section_color "couleurs"
 say canvas_color "canevas"
  say canvasbgedit "arri�re plan d'un canevas (edit mode)"
  say canvasbgrun "arri�re plan d'un canevas (run mode)"
 say object_color "objet"
  say viewframe1 "couleur de la boite d'objet"
  say viewframe2 "couleur de la boite d'objet"
  say viewframe3 "couleur de la boite d'objet"
  say viewframe4 "couleur du point culminant de la boite d'objet"
  say viewbg "arri�re plan d'un objet"
  say viewfg "arri�re plan d'un objet"
  say commentbg "arri�re plan d'un commentaire"
  say commentfg "premier plan d'un commentaire"
  say commentframe1 "comment frame"
  say commentframe2 "comment frame"
  say commentframe3 "comment frame"
  say viewselectframe "boite selectionn�e"
 say wire_color "cordon"
  say wirefg "couleur d'un cordon"
  say wirefg2 "couleur du point culminant d'un cordon"
  say wiredspfg "couleur d'un cordon DSP"
  say futurewiredash "nouveau cordon (en pointill�)"
 say others_color "autres"
  say boxinletfg "couleur de l'entr�e"
  say boxoutletfg "couleur de la sortie"
  say selrectrect "boite de selection"
say keys "touches"
say others "autres"
say canvashairstate "Activer le r�ticule"
say canvashairsnap "Crosshair snap to object" ;#TODO
say canvasstatusbar "Activer la barre du status"
say canvasbuttonbar "Activer la barre des boutons"
say wirewirearrow "Fl�che blanche"
say viewtooltip "ToolTip"
say canvasinsert_object "Ins�rer un objet"
say canvaschain_object "Encha�ner un objet"
say canvasclear_wires "Supprimer les cordons"
say canvasauto_wire "Supprimer un objet"
# phase 5A

say cannot "ne peut"
say cancel "Annuler"
say apply  "Appliquer"
say ok     "OK"
say popup_open "Ouvrir"
say popup_insert "Ins�rer"
say popup_properties "Propri�t�s"
say popup_clear_wires "Supprimer les cordons"
say popup_auto_wire "Supprimer l'objet"
say popup_help "Aide"
say filter "Filtre: "
say how_many_object_classes "%d of %d classes d'objet"
say do_what_i_mean "Fais ce que je te dis"
say ask_cool "�a serait cool, hein?"
say save_changes? "Sauvegarder les changements?"
say reset "Remise � zero"
say Courier     "Courier (chasse fixe)"
say Helvetica "Helvetica (sans s�rif)"
say Times         "Times (serif)"
say add "Ajouter"
say up "Vers le haut"
say down "Vers le bas"
say remove "Supprimer"
say lib_add    "Ajouter le nom � la liste"
say lib_up     "Inverser l'ordre avec la librairie pr�c�dente"
say lib_down   "Inverser l'ordre avec la librairie suivante"
say lib_remove "Supprimer la librairie selectionn�e dans la liste"
say dir_add    "Ajouter un dossier avec la boite de dialogue"
say dir_up     "Inverser l'ordre avec le dossier pr�c�dent"
say dir_down   "Inverser l'ordre avec le dossier suivant"
say dir_remove "Supprimer le dossier selectionn� dans la liste"
say client_class_tree "Arbre des classes du client"
say clipboard_view "Vue du presse-papier"
say command_history_view "Vue de l'historique de commandes"
say event_history_view "Vue de l'historique d'�v�nements"

# during/after piksel:

say auto_apply "Appliquer automatiquement"
say font_preview "Aper�u"
say font_preview_2 "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789"
say font_style "Style:"
say font_bold "Gras"
say font_italic "Italique"
say font_family "Nom:"
say font_size "Taille:"
say damn "Zut alors!"
say console_clear "Effacer la console"
say horizontal "Horizontal"
say vertical "Vertical"
say tcl_console "Client Tcl"
say pd_console "Serveur Pd"

# 2007:

say no_matches "(non trouv�)"
say preset "pr�r�glage"
say canvasgrid "Couleur du grillage"
say grid_size "Taille du grillage"
say gridstate "Activer le grillage de fond"
say snap_grid "Snap to grid" ;#TODO
say viewfont "police de l'objet"
say consolefont "police de la console"
say keyboarddialogfont "police du clavier virtuel"
say keyboard_view "Clavier virtuel"
say log_height "Log Height" ;#TODO
say visual_diff "Visual diff" ;#TODO
say auto "Auto"

# 2009:

say oops "Oupse..."
say oops_text "Ce programme a effectu� une op�ration niaiseuse et a �t� zigouill�."

