//Los cursos se numeran desde 1: el 0 significa "hora libre".
//Devuelve el numero de horas libres (el largo del cromosoma).
int crearHorario(vector<int>& H, int n_cursos=7, int clases=2){//clases de 3 horas
	H.resize(144,0);//6dias*24horas
	for (int i=0;i<n_cursos;i++){
		for (int j=0;j<clases;j++){
			int pos=XorShift(144);
			int cant=0;
			while(cant<3){
				while(H[pos]!=0 || (pos%24)<7 || (pos%24)>21){
					pos=(pos+1)%144;
				}
				H[pos]=i+1;
				cant++;
			}
		}
	}
	int l=0;
	for (int i=0;i<144;i++){
		if(H[i]==0){
			l++;
		}
	}
	cout << l << endl;
	return l;
}

//PROBLEMA DE HORARIO DE ESTUDIO
void imprimirHorario(vector<int>& H){
	if(H.size()!=144){
		return;
	}
	for (int i=0;i<6;i++){
		for (int j=0;j<24;j++){
			cout << H[i*24+j] << " ";
		}
		cout << endl;
	}
}
