#include "Model.h"
Model::Model(std::string model_filename, std::string texture_filename) {
	objl::Loader loader;
	loader.LoadFile(model_filename);
	std::cout << loader.LoadedMeshes[0].Vertices.size() << std::endl;

	for (int i = 0; i < loader.LoadedMeshes[0].Indices.size(); i++) {
		int vertexIndex = loader.LoadedMeshes[0].Indices[i];
		vertices.push_back(glm::vec3(
			loader.LoadedMeshes[0].Vertices[vertexIndex].Position.X,
			loader.LoadedMeshes[0].Vertices[vertexIndex].Position.Y,
			loader.LoadedMeshes[0].Vertices[vertexIndex].Position.Z));

		textureCoords.push_back(glm::vec2(
			loader.LoadedMeshes[0].Vertices[vertexIndex].TextureCoordinate.X,
			loader.LoadedMeshes[0].Vertices[vertexIndex].TextureCoordinate.Y));
	}

	if (!texture.loadFromFile(texture_filename))
	{
		std::cout << "Could not load texture file " << texture_filename << std::endl;
	}

	//sends the image to the GPU and stores a reference to it as an id value.
	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,  //mip-map level
		GL_RGBA, //We want the internal texture to have RGBA components
		texture.getSize().x, texture.getSize().y,// size of texture
		0, //border (0=no border, 1=border)
		GL_RGBA, //format of the external texture data
		GL_UNSIGNED_BYTE,
		texture.getPixelsPtr() //pointer to array of pixel data 
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


/* Use Guide:
in your draw call:

	sf::Texture::bind(&texture);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++) {
		glTexCoord2f(textureCoords[i].x, textureCoords[i].y);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	sf::Texture::bind(NULL);
	glEnd();

*/