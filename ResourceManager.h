///ResourceManager.h

class ResourceManager{
public:
  int init();
  
  RawModel loadToVAO(float[] positions, int numVerticies);
  
private:
  int createVAO();
  void storeDataInAttribList(int attribNum, float[] data);
  void unbindVAO();
}