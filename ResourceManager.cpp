///ResourceManager.cpp

int ResourceManager::init(){
  
}

RawModel ResourceManager::loadToVAO(float[] positions, int numVerticies){
  int vaoID = createVAO();
  storeDataInAttribList(0, positions);
  unbindVAO();
  RawModel model;
  model.init(vaoID, positions);
  return 
}

int ResourceManager::createVAO(){
  int vaoID = glGenVertexArrays();
  glBindVertexArrays(vaoID);
  return vaoID;
}

void ResourceManager::storeDataInAttribList(int attribNum, float[] data){
  int vboID = glGenBuffers();
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, data, GL_STATIC_DRAW);
  glVertexAttribPointer(attribNum, 3, GL_FLOAT, false, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ResourceManager::unbindVAO(){
  glBindVertexArrays(0);
}