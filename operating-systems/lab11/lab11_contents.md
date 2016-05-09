Concepte
========
   - Ce e un pipe
   - ->==============-> (schematic, cum arata un pipe)
   - crearea unui pipe cu `pipe(p)`
   - util de folosit in contextul aplicatiilor cu fork, pt. ca se pastreaza
     valoarea vectorului ala `p`
   - `p[0]` e pentru read si `p[1]` e pentru write.
   - se face `close(p[1])` din procesul care citeste, pt. ca oricum ala n-o sa
     scrie nimic. Analog, si ala care scrie isi va inchide capul de citire.
