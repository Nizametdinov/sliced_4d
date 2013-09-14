#ifndef __Vector4f_h_
#define __Vector4f_h_

class Vector4f
{
public:
	Vector4f(void);
	Vector4f(float w, float x, float y, float z);
	Vector4f(const Vector4f &v);
	~Vector4f(void);

	Vector4f& operator = (const Vector4f &v);
	float operator [] (size_t i) const;
	float& operator [] (size_t i);

	bool operator == (const Vector4f &v) const;
	inline bool operator != (const Vector4f &v) const 
	{
		return !operator == (v);
	}

	float length() const;
	float squaredLength() const;
	void normalise();

	float normMaxAbs() const;

	Vector4f& operator *= (float a);
	Vector4f& operator /= (float a);
	Vector4f& operator += (const Vector4f &v);
	Vector4f& operator -= (const Vector4f &v);

	Vector4f operator * (float a) const;
	Vector4f operator / (float a) const;
	Vector4f operator + (const Vector4f &v) const;
	Vector4f operator - (const Vector4f &v) const;
    Vector4f operator - () const;
	float operator * (const Vector4f &v) const;
private:
	float mValue[4];

	friend Vector4f operator * (float a, const Vector4f &v);
};

Vector4f operator * (float a, const Vector4f &v);

#endif //__Vector4f_h_