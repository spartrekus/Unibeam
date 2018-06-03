#/bin/sh

    echo Just Run 
    wget "https://raw.githubusercontent.com/spartrekus/Linux-Logos-Imgs/master/Tux-Logos/220px-Tux.png"   -O tux.png
    wget "https://upload.wikimedia.org/wikipedia/commons/5/56/Tux.jpg" -O tux.jpg 
    ###wget "https://raw.githubusercontent.com/spartrekus/Latex-Scientific-Presentation/master/scientific-presentation.bmr" -O presentation.bmr 
    wget "https://raw.githubusercontent.com/spartrekus/Latex-Scientific-Presentation/master/sciences-slides.bmr" -O presentation.bmr 

    echo Just View Using MUPDF 
    unimake presentation.bmr 


