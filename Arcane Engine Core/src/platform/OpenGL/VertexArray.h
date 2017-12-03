#pragma once

//Dependancies
#include "../../Dependancies.h"

//STL Includes
#include <vector>

//Operation Skullrain Headers
#include "Buffer.h"

namespace arcane { namespace opengl {

	class VertexArray {
	private:
		GLuint m_VertexArrayID;
		std::vector<Buffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer *buffer, int index);
		void bind() const;
		void unbind() const;
	};

} }