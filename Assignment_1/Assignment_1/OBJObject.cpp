#include "OBJObject.h"

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
}

//TODO: CHECK
void OBJObject::parse(const char *filepath) 
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    float r,g,b;  // vertex color
    int c1,c2;    // characters read from file
    int matches;
    
    //temp vertices

    
    fp = fopen(filepath,"rb");  // make the file name configurable so you can load other files
    
    if (fp == NULL) { cerr << "error loading file" << endl; exit(-1); }  // just in case the file can't be found or is corrupt
    
   // inputFile.open()
    //BAD FORM
    while(fp){
        
        c1 = fgetc(fp);
        c2 = fgetc(fp);

        if ((c1=='v') && (c2==' '))
        {
            glm::vec3 vertex;
            glm::vec3 temp_color;

          fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);

            vertex.x = x;
            vertex.y = y;
            vertex.z = z;
            vertices.push_back(vertex);
            
            temp_color.x = glm::normalize(r);
            temp_color.y = glm::normalize(g);
            temp_color.z = glm::normalize(b);
            colors.push_back((temp_color));
            
        }
        else if((c1 == 'v') && (c2=='n')) {
        
            glm::vec3 normal;

       //     cerr<<"here"<<endl;
            fscanf(fp, "%f %f %f ", &x, &y, &z);
            normal.x = x;
            normal.y = y;
            normal.z = z;
            normals.push_back((normal));
            
        }
        else if ((c1 == 'f') && (c2 == ' ')){
          //  cerr<<"where"<<endl;
        
            std::string vertex1, vertex2, vertex3;
            int vertexIndex[3], normalIndex[3];
            
             matches = fscanf(fp, "%d//%d %d//%d %d//%d", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
          
        //    cerr<<"matches "<<matches<<endl;
           if (matches != 6){
              //  printf("File can't be read by our simple parser ");
                break;
            }
            
       //     cerr<<"reach"<<endl;
            indices.push_back(vertexIndex[0]);
            indices.push_back(vertexIndex[1]);
            indices.push_back(vertexIndex[2]);
            indices.push_back(normalIndex[0]);
            indices.push_back(normalIndex[1]);
            indices.push_back(normalIndex[2]);
        
            //cerr<<"vectorIndices4 "<<vectorIndices[4]<<endl;
      
        }
        else{
            
        //nothing
        }
      
    }
    
    fclose(fp);   // make sure you don't forget to close the file when done
   // draw();
 
}

//meshing data
void OBJObject::draw() 
{
    glMatrixMode(GL_MODELVIEW);
    
    // Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(&(toWorld[0][0]));
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    // Loop through all the vertices of this OBJ Object and render them
    //cerr<<vertices[1].x<<vertices[1].y<<endl;
  
  //  glEnable (GL_COLOR_MATERIAL);

    for (unsigned int i = 0; i < vertices.size(); ++i)
    {
      //  cerr<<"r "<<(float)colors[i].x<<endl;
        //glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
        glColor3f(glm::normalize(normals[i].x), glm::normalize(normals[i].y), glm::normalize(normals[i].z));
        
      
    }

    
    glEnd();
    
    // Pop the save state off the matrix stack
    // This will undo the multiply we did earlier
    glPopMatrix();
}

void OBJObject:: update(){

     spin(0.01f);
}

void OBJObject::spin(float deg)
{
    this->angle += deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    
    // This creates the matrix to rotate the cube
    //glRotatef(angle, 0.0f, 1.0f, 0.0f);
   toWorld = toWorld * glm::rotate(glm::mat4(1.0f), deg, glm::vec3(0.0f, 1.0f, 0.0f));
}

void OBJObject::translation(float x, float y , float z){
    
    glm::vec3 multi (x,y,z);
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), multi);
    toWorld = toWorld * (trans);
    
}

void OBJObject::rotate(float d){

  /*  this -> angle += d;
    
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), d, glm::vec3(0.0f,1.0f,0.0f));
    toWorld = toWorld * rot;*/

}

void OBJObject::Drawable(const char * filepath, OBJObject *& object){

//    object = new OBJObject(filepath);
    //object = *obj;
    
}

void OBJObject::DrawBunny (OBJObject *& object){



}
void OBJObject::DrawDragon (OBJObject *& object){}
void OBJObject::DrawBear (OBJObject *& object){}



