//inicializo head
for (i=0; i<b^3;j++){
  *(head+i)=-1;
}

//armo listcell (lscl)
for (i=0;i<n;i++){
  h = (int)(x/(r_c + r_skin));
  k = (int)(y/(r_c + r_skin));
  l = (int)(z/(r_c + r_skin));
  c = h*b^2 + k * b + l;
  j = *(head+c);
  *(lscl+i)=j;
  *(head+c)=i;
}

//ahora recorro las celdas, y en cada una solo miro a los vecinos hh, kk, ll
int evaluar(){
  for (h=0; h<b; h++){
    for (k=0; k<b; k++){
      for (l=0; l<b; l++){
        c = h*b^2 + k * b + l;
        for (hh=h-1; hh<h+2; hh++){
          for (kk=k-1; kk<k+2; kk++){
            for (ll=l-1; ll<l+2; ll++){
              //algo, calculo de fuerzas.
              cc = hh*b^2 + kk * b + ll;
              z = *(head+c);
              //blalbalba
              while(z != -1){
                zz = *(head + cc);
                while(zz != -1){
                  if (z < zz){
                    if(r^2<r_c^2){//podria evitarse este if, pero si tomo valores de tabla tiene que estar
                        //evaluar fuerzas
                        //estamos contando las fuerzas dos veces??
                    }//end if rc
                  }//end if z
                  zz = *(lscl+zz)
                }//end while zz
              }//end while z
            }//end loop ll
          }//end loop kk
        }//end loop hh
      }//end loop l
    }//end loop k
  }//end loop h
  return 0;
}
