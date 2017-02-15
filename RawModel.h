///RawModel.h

class RawModel{
public:
  
  int getVaoID(){ return vaoID; }
  int getVertexCount(){ return vertexCount; }
  
private:
  int vaoID;
  int vertexCount;
}