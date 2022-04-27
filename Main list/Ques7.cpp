#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
class Matrix3D{
    public:
    float **arr;
    int r,c;
    Matrix3D(){}
    Matrix3D(int r, int c){
        this->r = r;
        this->c = c;
        this->arr = new float* [r];
        for(int i = 0; i < r; i++){
            arr[i] = new float[c];
        }
    }
    int* getPlotPoints(){
        int *points = new int[r*2];
        int k=0;
        for(int i =0 ; i<r;i++){
            points[k++] = (int) arr[i][0];
            points[k++] = (int) arr[i][1];            
        }
        points[k++] = (int) arr[0][0];
        points[k++] = (int) arr[0][1];
        // for(int i =0; i<=2*r; i+=2){
        //     cout<<points[i]<<","<<points[i+1]<<"\n";
        // }
        return points;
    }
    void setMatrix(float a[][4]){
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                this->arr[i][j] = a[i][j];
            }
        }
    }
    void printMatrix(){
        for(int i =0 ; i < r; i++){
            cout<<"[ ";
            for(int j = 0; j <c; j++){
                cout<<arr[i][j]<<" ";
            }
            
            i==r-1 ? printf("](%d,%d)\n",r,c): printf("]\n");
        }
    }
    static Matrix3D multiply(Matrix3D m1, Matrix3D m2){
        Matrix3D m(m1.r, m2.c);
        for(int i = 0; i < m1.r; i++){
            for(int j = 0; j < m2.c ; j++){
                for(int k = 0; k < m1.c ; k++){
                    m.arr[i][j] += m1.arr[i][k]*m2.arr[k][j];
                }
            }
        }
        return m;
    }
    static Matrix3D multiply(Matrix3D* m1, Matrix3D m2){
        Matrix3D m(m1->r, m2.c);
        for(int i = 0; i < m1->r; i++){
            for(int j = 0; j < m2.c ; j++){
                for(int k = 0; k < m1->c ; k++){
                    m.arr[i][j] += m1->arr[i][k]*m2.arr[k][j];
                }
            }
        }
        return m;
    }
};
class Projection{
    private:
        Matrix3D *points;
        int orthographic(){
            cout<<"\nPARALLEL: ORTHOGRAPHIC PROJECTION***\n";
            Matrix3D trf(4,4);
            float t[][4]={
                {1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {0,0,0,1},
            };
            cout<<"Enter projection on:\n";
            cout<<"\n1.X=0 plane\n2.Y=0 plane\n3.Z=0 plane\n: ";
            int ortho;
            cin>>ortho;
            if(ortho == 1){
                t[0][0] = 0;
            }else if(ortho == 2){
                t[1][1] = 0;
            }else if(ortho == 3){
                t[2][2] = 0;
            }else{
                cout<<"Invalid choice";
                return 0;
            }
            trf.setMatrix(t);
            cout<<"\nTransformation matrix:\n";
            trf.printMatrix();
            cout<<"\nOriginal points:\n";
            this->points->printMatrix();
            Matrix3D result = Matrix3D::multiply(this->points, trf);
            cout<<"\nTransformed points: \n";
            result.printMatrix();
            return 0;
        }
        int oblique(){
            cout<<"\n***PARALLEL: OBLIQUE PROJECTION***\n";
            cout<<"***(Taking horizontal inclination angle = 30 degree)***\n";
            Matrix3D trf(4,4);
            float t[][4]={
                {1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {0,0,0,1},
            };
            cout<<"Enter your choice:\n";
            cout<<"\n1.Cavalier projection\n2.Cabinet projection\n: ";
            int ob;
            cin>>ob;
            if(ob == 1){
                t[2][0] = -0.866;
                t[2][1] = -0.5;
            }else if(ob == 2){
                t[2][0] = -0.433;
                t[2][1] = -0.25;
            }else{
                cout<<"Invalid choice";
                return 0;
            }
            trf.setMatrix(t);
            cout<<"\nTransformation matrix:\n";
            trf.printMatrix();
            cout<<"\nOriginal points:\n";
            this->points->printMatrix();
            Matrix3D result = Matrix3D::multiply(this->points, trf);
            cout<<"\nTransformed points: \n";
            result.printMatrix();
            return 0;
        }
        int axonometric(){
            cout<<"\nPARALLEL: AXONOMETRIC PROJECTION***\n";
            cout<<"***(Onto Z=0 plane)***\n";
            Matrix3D trf(4,4);
            float t[][4]={
                {1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {0,0,0,1},
            };
            cout<<"Enter your choice:\n";
            cout<<"\n1.Trimetric projection\n2.Dimetric projection\n3.Isometric projection\n: ";
            int axono;
            cin>>axono;
            if(axono == 1){
                t[2][2] = 0;
                int theta, phi;
                cout<<"Enter angle for first rotation: ";
                cin>>phi;
                cout<<"Enter angle for second rotation: ";
                cin>>theta;
                float sintheta;
                sintheta = sin(theta*3.14159/180);

                t[0][0] = cos(phi*3.14159/180);
                t[2][0] = sin(phi*3.14159/180); 
                
                t[0][1] = sintheta * t[2][0];
                t[1][1] = cos(theta*3.14159/180);
                t[2][1] = -1*sintheta*t[0][0];

            }else if(axono == 2){
                t[2][2] = 0;
                float fz,phi,theta,sintheta;
                cout<<"Enter foreshortening factor Fz:  ";
                cin>>fz;
                phi = fz / (float) sqrt(2 - fz*fz);
                theta = fz / (float) sqrt(2);
                cout<<"Angle for first rotation (phi): "<<phi<<" degree\n";
                cout<<"Angle for second rotation (theta): "<<theta<<" degree\n";

                sintheta = sin(theta*3.14159/180);

                t[0][0] = cos(phi*3.14159/180);
                t[2][0] = sin(phi*3.14159/180); 
                
                t[0][1] = sintheta * t[2][0];
                t[1][1] = cos(theta*3.14159/180);
                t[2][1] = -1*sintheta*t[0][0];


            }else if(axono == 3){
                t[2][2] = 0;
                cout<<"Taking Angle for first rotation (phi): -45 degree\n";
                cout<<"Taking Angle for second rotation (theta): 35.26 degree";
                t[0][0] = 0.707;
                t[2][0] = -0.707;
                
                t[0][1] = -0.408;
                t[1][1] =  0.816;
                t[2][1] = -0.408;
            }else{
                cout<<"Invalid choice";
                return 0;
            }
            trf.setMatrix(t);
            cout<<"\nTransformation matrix:\n";
            trf.printMatrix();
            cout<<"\nOriginal points:\n";
            this->points->printMatrix();
            Matrix3D result = Matrix3D::multiply(this->points, trf);
            cout<<"\nTransformed points: \n";
            result.printMatrix();
            return 0;
        }

        int parallel(){
            cout<<"\n***PARALLEL PROJECTION***\n";
            int choicep1;
            cout<<"Enter your choice:\n";
            cout<<"\n1.ORTHOGRAPHIC\n2.AXONOMETRIC\n3.OBLIQUE\n: ";
            cin>>choicep1;
            switch (choicep1)
            {
            case 1:
                orthographic();
                break;
            case 2:
                axonometric();
                break;
            case 3:
                oblique();
                break;
            default: cout<<"Invalid choice.";
                break;
            }
            return 0;
        }
        int perspective(){
            cout<<"\n***PERSPECTIVE PROJECTION***\n";
            cout<<"***(Onto Z=0 plane)***\n";
            cout<<"***(Taking p,q,r to be 0.1 in all 3 cases)***\n";
            Matrix3D trf(4,4);
            float t[][4]={
                {1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {0,0,0,1},
            };
            cout<<"Enter your choice:\n";
            cout<<"1.One point projection\n2.Two point projection\n3.Three point projection\n: ";
            int pers;
            cin>>pers;
            if(pers == 1){
                t[2][2] = 0;
                t[0][3] = 0.1;
            }else if(pers == 2){
                t[2][2] = 0;
                t[0][3] = 0.1;
                t[1][3] = 0.1;
            }else if(pers == 3){
                t[2][2] = 0;
                t[0][3] = 0.1;
                t[1][3] = 0.1;
                t[2][3] = 0.1;
            }else{
                cout<<"Invalid choice";
                return 0;
            }
            trf.setMatrix(t);
            cout<<"\nTransformation matrix:\n";
            trf.printMatrix();
            cout<<"\nOriginal points:\n";
            this->points->printMatrix();
            Matrix3D result = Matrix3D::multiply(this->points, trf);
            cout<<"\nTransformed points: \n";
            result.printMatrix();
            return 0;
        }
    public:
        int exec(){
            int choice;
            while(true){
                cout<<"\n\n Select the type of projection:\n";
                cout<<"1.Perspective\n2.Parallel\n3.Exit\n:";
                cin>>choice;
                switch (choice)
                {
                case 1:
                    perspective();
                    break;
                case 2:
                    parallel();
                    break;
                case 3:
                    return 0;
                default:
                    cout<<"Invalid choice, try again.";
                    break;
                }
            }
           return 0; 
        }
        Projection(Matrix3D *t){
            this->points = t;
        }
};
class transform3d{
    public:
        Matrix3D *p;
    transform3d(){p = NULL;}
    ~transform3d(){
        
    }
    void getPoints(){
        int n;
        cout<<"Enter no of points: ";
        cin>>n;
        
        p = new Matrix3D(n,4);
        float x,y,z;
        for(int i = 0; i < n; i++){
            printf("Point %d\nEnter x co-ordinate: ", i+1);
            cin>>x;
            cout<<"Enter y co-ordinate: ";
            cin>>y;
            cout<<"Enter z co-ordinate: ";
            cin>>z;            
            p->arr[i][0] = x;
            p->arr[i][1] = y;
            p->arr[i][2] = z; 
            p->arr[i][3] = 1; 
        }
        cout<<"Points matrix is:\n";
        p->printMatrix();
    }
    void setPoints(int n,float arr[][4]){
       
        p = new Matrix3D(n,4);
        p->setMatrix(arr);
    }
    void translate(){
        float tx, ty,tz;
        cout<<"Enter translation in x-axis: ";
        cin>>tx;
        cout<<"Enter translation in y-axis: ";
        cin>>ty;
        cout<<"Enter translation in z-axis: ";
        cin>>tz;

        float t[4][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {tx,ty,tz,1}         
        };
        Matrix3D trf(4,4);
        trf.setMatrix(t);
        cout<<"\nTransformation matrix:\n";
        trf.printMatrix();
        cout<<"\nOriginal points:\n";
        this->p->printMatrix();
        Matrix3D result = Matrix3D::multiply(this->p, trf);
        cout<<"\nTransformed points: \n";
        result.printMatrix();        
    }   
    void scale(){
        float sx, sy,sz;
        cout<<"Enter X-axis scaling factor: ";
        cin>>sx;
        cout<<"Enter Y-axis scaling factor: ";
        cin>>sy;
        cout<<"Enter Z-axis scaling factor: ";
        cin>>sz;
        
        float t[4][4] = {
            {sx,0,0,0},
            {0,sy,0,0},
            {0,0,sz,0},
            {0,0,0,1}         
        };
        Matrix3D trf(4,4);
        trf.setMatrix(t);
        cout<<"\nTransformation matrix:\n";
        trf.printMatrix();
        cout<<"\nOriginal points:\n";
        this->p->printMatrix();
        Matrix3D result = Matrix3D::multiply(this->p, trf);
        cout<<"\nTransformed points: \n";
        result.printMatrix();        
    }
    void rotate(){
        float thetaR, thetaD;
        cout<<"Enter angle of rotation, in degrees";
        cin>>thetaD;
        thetaR = thetaD * 3.14159/180;
        float cosT = (float) cos(thetaR);
        float sinT = (float) sin(thetaR);
        float t[4][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}         
        };
        bool flag = true;
        while(flag){
            int choice;
            cout<<"\nRotate about:\n1.X-Axis\n2.Y-Axis\n3.Z-Axis: ";
            cin>>choice;
            switch (choice)
            {
                case 1:
                    t[1][1] = t[2][2] = cosT;
                    t[1][2] = -1*sinT;
                    t[2][1] = sinT;
                    flag = false;
                    break;
                case 2:
                    t[0][0] = t[2][2] = cosT;
                    t[0][2] = sinT;
                    t[2][0] = -1*sinT;
                    flag = false;
                    break;
                case 3:
                    t[0][0] = t[1][1] = cosT;
                    t[0][1] = -1*sinT;
                    t[1][0] = sinT;
                    flag = false;
                    break;
                default: cout<<"Invalid choice, try again";
                }
        }
        Matrix3D trf(4,4);
        trf.setMatrix(t);
        cout<<"\nTransformation matrix:\n";
        trf.printMatrix();
        cout<<"\nOriginal points:\n";
        this->p->printMatrix();
        Matrix3D result = Matrix3D::multiply(this->p, trf);
        cout<<"\nTransformed points: \n";
        result.printMatrix();        
    }
    void reflect(){
        float t[4][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}         
        };
        bool flag = true;
        while(flag){
            cout<<"\nReflect about:\n1.X-Axis\n2.Y-Axis\n3.Z-Axis: ";
            int choice;
            cin>>choice;
            switch (choice)
            {
                case 1:
                    t[1][1] = t[2][2] = -1;
                    flag = false;
                    break;
                case 2:
                    t[0][0] = t[2][2] = -1;
                    flag = false;
                    break;
                case 3:
                    t[0][0] = t[1][1] = -1;
                    flag = false;
                    break;
                default: cout<<"Invalid choice, try again";
                }
        }
        Matrix3D trf(4,4);
        trf.setMatrix(t);
        cout<<"\nTransformation matrix:\n";
        trf.printMatrix();
        cout<<"\nOriginal points:\n";
        this->p->printMatrix();
        Matrix3D result = Matrix3D::multiply(this->p, trf);
        cout<<"\nTransformed points: \n";
        result.printMatrix();       
    }
};

int main(){
    transform3d t;
    t.getPoints();
    Projection p(t.p); 
    while(true){
        cout<<"\nEnter your choice:\n";
        cout<<"1.Translate\n2.Scale\n3.Rotate\n4.Reflect\n5.Projection\n6.Show points\n7.Change points\n8.Exit\n: ";
        int choice;
        cin>>choice;
        switch(choice)
        {
        case 1:
            t.translate();
            break;
        case 2:
            t.scale();
            break;
        case 3:
            t.rotate();
            break;
        case 4:
            t.reflect();
            break;
        case 5:
            p.exec();
        case 6:
            cout<<"\nPoints Matrix is:\n";
            t.p->printMatrix();
            break;
        case 7:
            t.getPoints();
            break;
        case 8:
            return 0;
        default:
            cout<<"\nInvalid choice. Please try again";
            break;
        }
    }
    return 0;
}
