#!/bin/bash

case `file -b $1 | cut -d "," -f 1` in
'JPEG image data'|'PNG image data'|'PC bitmap')
	echo "Eine Bilddatei"  
	/usr/local/bin/xv $1 
	;;
'OpenDocument Text')
	echo "OpenDocument"
	/usr/local/bin/libreoffice $1 
	;;
'PDF document')
	echo "PDF"
	/usr/local/bin/xpdf $1 
	;;
'ASCII text')
	echo "Text"
	less $1 
	;;
*)
	echo "Diesen Dateityp unterstuetze ich nicht"
    ;;
esac
