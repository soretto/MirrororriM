#pragma once

#include	<simplemath.h>
#include	<string>
#include	<vector>
#include	<memory>
#include	"Texture.h"
#include	"Mesh.h"
#include	"renderer.h"

class StaticMesh : public Mesh {
public:
	void Load(std::string filename, std::string texturedirectory="");

	const std::vector<MATERIAL>& GetMaterials() {
		return m_materials;
	}

	const std::vector<SUBSET>& GetSubsets() {
		return m_subsets;
	}

	const std::vector<std::string>& GetTextureNames() {
		return m_texturenames;
	}

	std::vector<std::unique_ptr<Texture>> GetTextures() {
		return std::move(m_textures);
	}

private:

	std::vector<MATERIAL> m_materials;					// �}�e���A�����
	std::vector<std::string> m_texturenames;			// �e�N�X�`����
	std::vector<SUBSET> m_subsets;						// �T�u�Z�b�g���
	std::vector<std::unique_ptr<Texture>>	m_textures;	// �e�N�X�`���Q
};