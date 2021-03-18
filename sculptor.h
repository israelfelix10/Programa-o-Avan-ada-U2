#ifndef SCULPTOR_H
#define SCULPTOR_H

#endif // SCULPTOR_H

#include <iostream>
#include <fstream>

using namespace std;

struct Voxel {
  float r,g,b; // Colors
  float a;
// Transparency
  bool isOn; // Included or not
};

class FiguraGeometrica {
protected:
  Voxel ***v;
  // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  FiguraGeometrica (int _nx, int _ny, int _nz);
  ~FiguraGeometrica();
  void setColor(float r, float g, float b, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void writeOFF(char* filename);
};

FiguraGeometrica::FiguraGeometrica(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v=new Voxel **[nx];
    for(int xs=0; xs<nx; xs++){
        v[xs]= new Voxel *[_ny];
    }
    for(int xs=0; xs<nx; xs++){
        for(int ys=0; ys<ny; ys++){
            v[xs][ys]= new Voxel [nz];
        }
    }

    for(int xs=0; xs<nx; xs++){
        for(int ys=0; ys<ny; ys++){
            for(int zs=0; zs<nz; zs++){
               v[xs][ys][zs].isOn=false;
               v[xs][ys][zs].r=r;
               v[xs][ys][zs].g=g;
               v[xs][ys][zs].b=b;
               v[xs][ys][zs].a=a;
            }
        }
    }
//Obrigado a @mindsidi
}
FiguraGeometrica::~FiguraGeometrica(){

    int ax, ay;
    ax=nx;
    ay=ny;
    for(int as=0; as<ax; as++){
        for(int ass=0; ass<ay; ass++){
            delete[] v[as][ay];
        }
    }
    for(int as=0; as<ax; as++){
        delete [] v[as];
    }
    delete [] v;
 //Obrigado a @mindsidi
}
void FiguraGeometrica::setColor(float r, float g, float b, float alpha)
{
    this->r=r;
    this->g=g;
    this->b=b;
    this->a=alpha;

 //Obrigado a @mindsidi
}
void FiguraGeometrica::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
    //Obrigado a @mindsidi
}

void  FiguraGeometrica :: cutVoxel ( int x, int y, int z)
{
    v[x][y][z].isOn = false ;
    //Obrigado a @mindsidi
}


void FiguraGeometrica::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
               putVoxel(i,j,k);
            }
        }
    }
 //Obrigado a @mindsidi
}
void FiguraGeometrica::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
 //Obrigado a @mindsidi
}

void FiguraGeometrica::writeOFF(char* filename)
{
    ofstream fout;
    int Nvertices=0;
    int Nfaces=0;
    int aux=0;
    fout.open(filename);

    if(fout.is_open()){
        cout << "Aguarde...Salvando o arquivo OFF.\n";
    }
    else{
        cout << "Arquivo OFF nao foi aberto\n";
        exit(1);
    }

    fout<<"OFF"<<endl;

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].isOn){
                    Nvertices=Nvertices+8;
                    Nfaces=Nfaces+6;
                }
            }
        }
    }

    fout<<Nvertices<<" "<<Nfaces<<" "<<0<<endl;

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].isOn){
                        fout<<i-0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout<<i-0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout<<i+0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout<<i+0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout<<i-0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                        fout<<i-0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout<<i+0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout<<i+0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                }
            }
        }
    }

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].isOn){
                    fout<<4<<" "<<aux+0<<" "<<aux+3<<" "<<aux+2<<" "<<aux+1<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+4<<" "<<aux+5<<" "<<aux+6<<" "<<aux+7<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+0<<" "<<aux+1<<" "<<aux+5<<" "<<aux+4<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+0<<" "<<aux+4<<" "<<aux+7<<" "<<aux+3<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+3<<" "<<aux+7<<" "<<aux+6<<" "<<aux+2<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+1<<" "<<aux+2<<" "<<aux+6<<" "<<aux+5<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    aux=aux+8;
                }
            }
        }
    }

    if(fout.is_open()){
        cout << "Arquivo.OFF salvo!"<<endl;
    }
//Obrigado a @kaiquecodes
}
