#include <rendering/Tesselator.hpp>
#include <unigl.hpp>
#include <_types.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <rendering/states/EnableClientState.hpp>

Tesselator Tesselator::instance(0x800000);

Tesselator::Tesselator(int32_t size)
	: field_4C(0), field_50(0), tmat4x4_2(1.0f)
	, vec(0, 0, 0) {
	this->textureU = 0.0;
	this->textureV = 0.0;
	this->color_int = 0;
	this->normX = this->normY = this->normZ = this->field_7B = 0;
	this->scale2 = 1.0;
	this->scale1 = 1.0;
	this->scale3 = 1.0;
	this->scale4 = 1.0;
	this->scale5 = 1.0;
	this->isTilted = 0;
	this->isColorDisabled = 0;
	this->accessMode = 2;
	this->field_D6 = 0;
	this->vertexCount = 0;
	this->maxVertextNumber = 0;
	this->isDrawing = 0;
	this->bufSize = size;
	this->field_E8 = 0;
	this->drawMode = 0;

	this->tmat4x4_2 = glm::rotate<float>(glm::mat4x4(1.0f), 210.0, glm::vec3(1, 0, 0));
	this->tmat4x4_2 = glm::rotate<float>(this->tmat4x4_2, 45.0, glm::vec3(0, 1, 0));
}

void Tesselator::_buildQuadIndexBuffer() {
	this->setMaxVertexNumber(this->maxVertextNumber);
	int32_t v2 = 0;
	while(v2 < this->maxVertextNumber) {
		uint16_t v3 = v2;
		v2 += 4;
		this->quad(v3, 0);
	}
}

void Tesselator::addOffset(const Vec3& v) {
	this->vec.x += v.x;
	this->vec.y += v.y;
	this->vec.z += v.z;
}

void Tesselator::addOffset(float x, float y, float z) {
	this->vec.x += x;
	this->vec.y += y;
	this->vec.z += z;
}

void Tesselator::begin(int32_t m) {
	this->begin(7, m);
}

void Tesselator::begin(int32_t mode, int32_t a3) {
	if(!this->isDrawing) {
		if(!this->field_D6) {
			this->isDrawing = 1;
			this->clear();
			this->field_D4 = 1;
			this->drawMode = mode;
			this->isColorDisabled = 0; //=v6
			MeshBuffer::VertexFormat v8;
			uint8_t* uu = v8.offsets;
			this->meshBuffer_vf2.offsets[0] = uu[0];
			this->meshBuffer_vf2.offsets[1] = uu[1];
			this->meshBuffer_vf2.offsets[2] = uu[2];
			this->meshBuffer_vf2.offsets[3] = uu[3];

			this->meshBuffer_vf2.stride = v8.stride;
			this->meshBuffer_vf2.enableField(MeshBuffer::VertexFormat::Field::FIELD0);
			this->someSIzeMaybe = 0;
			this->vertexFormat = a3;
			this->useDrawElementsOrDrawArrays = 0;
		}
	}
}

void Tesselator::cancel() {
	this->isDrawing = 0;
}

void Tesselator::clear() {
	this->accessMode = 2;
	this->maxVertextNumber = 0;
	this->useDrawElementsOrDrawArrays = 0;
	this->vertexCount = 0;
	this->field_D6 = 0;
	this->vertexes.clear();
	this->field_14.clear();
}

void Tesselator::color(char r, char g, char b) {
	this->color((int32_t)r, (int32_t)g, (int32_t)b);
}

void Tesselator::color(float r, float g, float b) {
	this->color((int32_t)(r * 255), (int32_t)(g * 255), (int32_t)(b * 255));
}

void Tesselator::color(float r, float g, float b, float a) {
	this->color((int32_t)(r * 255), (int32_t)(g * 255), (int32_t)(b * 255), (int32_t)(a * 255));
}

void Tesselator::color(int32_t c) {
	this->color((c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff);
}

void Tesselator::color(int32_t c, int32_t a) {
	this->color((c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff, a);
}

void Tesselator::color(int32_t r, int32_t g, int32_t b) {
	this->color(r, g, b, 255);
}

void Tesselator::color(int32_t r, int32_t g, int32_t b, int32_t a) {
	if(this->isColorDisabled) return;

	//uses USAT instruction for rgba
	if(r < 0) r = 0;
	if(r > 255) r = 255;
	if(g < 0) g = 0;
	if(g > 255) g = 255;
	if(b < 0) b = 0;
	if(b > 255) b = 255;
	if(a < 0) a = 0;
	if(a > 255) a = 255;

	this->color_int = (r & 0xff) | (g << 8) | (b << 16) | (a << 24);
	if(this->field_D4) {
		this->meshBuffer_vf2.enableField(MeshBuffer::VertexFormat::Field::FIELD2);
	}
}
void Tesselator::colorABGR(int32_t a2) {
	if(this->isColorDisabled) return;
	this->color_int = a2;
	this->meshBuffer_vf2.enableField(MeshBuffer::VertexFormat::Field::FIELD2);
}

void Tesselator::draw(bool_t a2) {
	if(!this->isDrawing) return;
	if(this->field_D6) return;
	this->isDrawing = 0;
	if(this->getVertexCount() > 0) {
		EnableClientState v9, v10, v11;
		if(this->drawMode == 7) {
			this->_buildQuadIndexBuffer();
			this->drawMode = GL_TRIANGLES;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//TODO replace with gl constants
		Tesselator::CurrentVertexPointers v13(this->field_14.data(), this->meshBuffer_vf2);
		if(v13.hasTexture) {
			glTexCoordPointer(2, GL_FLOAT, this->meshBuffer_vf2.stride, v13.hasTexture);
			if(a2) {
				EnableClientState cs(GL_TEXTURE_COORD_ARRAY);
				v9 = cs;
				cs.enabled = 0;
			}
		}

		if(v13.hasColor) {
			glColorPointer(4, GL_UNSIGNED_BYTE, this->meshBuffer_vf2.stride, v13.hasColor);
			if(a2) {
				EnableClientState cs(GL_COLOR_ARRAY);
				v10 = cs;
				cs.enabled = 0;
			}
		}

		if(v13.hasNormals) {
			glNormalPointer(0x1400, this->meshBuffer_vf2.stride, v13.hasNormals);
			if(a2) {
				EnableClientState cs(GL_NORMAL_ARRAY);
				v11 = cs;
				cs.enabled = 0;
			}
		}

		glVertexPointer(3, GL_FLOAT, this->meshBuffer_vf2.stride, v13.field_0);
		if(this->useDrawElementsOrDrawArrays) {
			glDrawElements(this->drawMode, this->useDrawElementsOrDrawArrays, this->someSIzeMaybe != 2 ? 5121 : 5123, this->vertexes.data());
		} else {
			glDrawArrays(this->drawMode, 0, this->field_14.size() / this->meshBuffer_vf2.stride);
		}
	}
}

void Tesselator::enableColor() {
	this->isColorDisabled = 0;
}

MeshBuffer Tesselator::end(void) {
	int32_t drawMode; // r2

	if(!this->isDrawing || this->field_D6 || (this->isDrawing = 0, !this->maxVertextNumber) || this->field_D4) {
		return MeshBuffer();
	} else {
		if(this->drawMode == 7) {
			this->_buildQuadIndexBuffer();
		}

		drawMode = this->drawMode;
		if(drawMode == 7) {
			drawMode = 4;
		}
		MeshBuffer v7(this->_genVertexFormat(), this->field_14.data(), (this->field_14.size()) / (uint32_t)this->meshBuffer_vf2.stride, this->vertexes.data(), this->useDrawElementsOrDrawArrays, this->someSIzeMaybe, drawMode);
		this->field_E8 += this->field_14.size();
		this->clear();
		return v7; //TODO must copy?
	}
}

int32_t Tesselator::getColor(void) {
	return this->color_int;
}
int32_t Tesselator::getVertexCount(void) {
	return this->vertexCount;
}

void Tesselator::init() {
}
void Tesselator::noColor(void) {
	this->isColorDisabled = 1;
}
void Tesselator::normal(float x, float y, float z) {
	this->normX = (int8_t)(x * 127);
	this->normY = (int8_t)(y * 127);
	this->normZ = (int8_t)(z * 127);

	if(this->field_D4) {
		this->meshBuffer_vf2.enableField(MeshBuffer::VertexFormat::FIELD3);
	}
}
void Tesselator::offset(const Vec3& v) {
	this->vec = v;
}
void Tesselator::offset(float x, float y, float z) {
	this->vec.x = x;
	this->vec.y = y;
	this->vec.z = z;
}

void Tesselator::quad(uint16_t a2, bool_t a3) {
	if(a3) this->quad(a2 + 3, a2 + 2, a2 + 1, a2);
	else this->quad(a2, a2 + 1, a2 + 2, a2 + 3);
}

void Tesselator::quad(uint16_t a2, uint16_t a3, uint16_t a4, uint16_t a5) { //TODO
	int32_t useDrawElementsOrDrawArrays;									// r6
	uint8_t* vecStartPtr;													// r5
	uint8_t* v11;															// r0
	uint16_t* v12;															// r0

	if(!this->someSIzeMaybe) {
		this->someSIzeMaybe = 2;
	}
	this->vertexes.resize((this->useDrawElementsOrDrawArrays + 6) * this->someSIzeMaybe);
	useDrawElementsOrDrawArrays = this->useDrawElementsOrDrawArrays;
	vecStartPtr = this->vertexes.data();
	if(this->someSIzeMaybe == 1) {
		v11 = &vecStartPtr[useDrawElementsOrDrawArrays];
		vecStartPtr[useDrawElementsOrDrawArrays] = a2;
		v11[1] = a3;
		v11[2] = a4;
		v11[3] = a5;
		v11[4] = a2;
		v11[5] = a4;
	} else {
		v12 = (uint16_t*)&vecStartPtr[2 * useDrawElementsOrDrawArrays];
		*v12 = a2;
		v12[1] = a3;
		v12[2] = a4;
		v12[3] = a5;
		v12[4] = a2;
		v12[5] = a4;
	}
	this->useDrawElementsOrDrawArrays += 6;
}

void Tesselator::resetScale(void) {
	this->scale1 = this->scale2 = this->scale3 = this->scale4 = this->scale5 = 1;
}
void Tesselator::resetTilt(void) {
	this->isTilted = 0;
}
void Tesselator::scale2d(float a, float b) {
	this->scale2 *= a;
	this->scale1 *= b;
}
void Tesselator::scale3d(float a, float b, float c) {
	this->scale3 *= a;
	this->scale4 *= b;
	this->scale5 *= c;
}
void Tesselator::setAccessMode(int32_t a) {
	this->accessMode = a;
}

void Tesselator::setMaxVertexNumber(int32_t n) {
	this->vertexFormat = n;
	if(!this->someSIzeMaybe) {
		this->someSIzeMaybe = 2;
		this->vertexes.reserve(12 * (n / 4));
	}
}

void Tesselator::tex(float u, float v) {
	this->textureU = u;
	this->textureV = v;
	if(this->field_D4) {
		this->meshBuffer_vf2.enableField(MeshBuffer::VertexFormat::Field::FIELD1);
	}
}
void Tesselator::tilt(void) {
	this->isTilted = 1;
}
void Tesselator::vertex(float x, float y, float z) {
	++this->maxVertextNumber;
	int32_t vertexFormat = this->vertexFormat;
	uint8_t* vbegin = this->field_14.data();

	if(vertexFormat) {
		this->field_14.reserve(this->meshBuffer_vf2.stride * this->vertexFormat);
		this->vertexFormat = 0;
	}
	this->field_14.resize((this->vertexCount + 1) * this->meshBuffer_vf2.stride);

	if(this->field_D4 || vbegin != this->field_14.data()) {
		this->currentVertexPointers = Tesselator::CurrentVertexPointers(this->field_14.data() + this->vertexCount * this->meshBuffer_vf2.stride, this->meshBuffer_vf2);
		this->field_D4 = 0;
	} else {
		const MeshBuffer::VertexFormat* v19 = this->currentVertexPointers.field_10;
		this->currentVertexPointers.field_0 += v19->stride;
		if(this->currentVertexPointers.hasColor) this->currentVertexPointers.hasColor += v19->stride;
		if(this->currentVertexPointers.hasNormals) this->currentVertexPointers.hasNormals += v19->stride;
		if(this->currentVertexPointers.hasTexture) this->currentVertexPointers.hasTexture += v19->stride;
	}

	glm::vec4 v20(x, y, z, 1.0f);
	if(this->isTilted) {
		v20 = this->tmat4x4_2 * v20;
		x = v20[0];
		y = v20[1];
		z = v20[2];
	}

	*(float*)this->currentVertexPointers.field_0 = this->scale2 * (this->vec.x + (x * this->scale3));
	*((float*)this->currentVertexPointers.field_0 + 1) = this->scale1 * (this->vec.y + (y * this->scale3));
	*((float*)this->currentVertexPointers.field_0 + 2) = this->vec.z + (z * this->scale3);

	if(this->currentVertexPointers.hasTexture) {
		*(float*)this->currentVertexPointers.hasTexture = this->textureU;
		*((float*)this->currentVertexPointers.hasTexture + 1) = this->textureV;
	}

	if(this->currentVertexPointers.hasColor) {
		*(int32_t*)this->currentVertexPointers.hasColor = this->color_int;
	}

	if(this->currentVertexPointers.hasNormals) {
		*(int32_t*)this->currentVertexPointers.hasNormals = *(int32_t*)&this->normX;
	}

	++this->vertexCount;
}
void Tesselator::vertexUV(float x, float y, float z, float u, float v) {
	this->tex(u, v);
	this->vertex(x, y, z);
}
void Tesselator::voidBeginAndEndCalls(bool_t a2) {
	this->field_D6 = a2;
}
Tesselator::~Tesselator() {
	//i hope it calls destructors automatically
}
