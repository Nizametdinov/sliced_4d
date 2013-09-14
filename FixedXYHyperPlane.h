#ifndef __FixedXYHyperPlane_h_
#define __FixedXYHyperPlane_h_

#include "HyperPlane.h"

// �������������� � ������������� ���������� XY
// ������� ����� ��������� ����� ��� {cos(alpha), 0, 0, sin(alpha)},
// ��� alpha - ���� ������� ������ ��������� XY.
// ������������� alpha = 0, � ������� = {1, 0, 0, 0}
class FixedXYHyperPlane: public HyperPlane
{
public:
	FixedXYHyperPlane(void);
	~FixedXYHyperPlane(void);

	// ������� ������ ��������� ������������ XY ���������� ����� fixedPoint
	// ��� ���������� ������� RotateAroundXY ��� ����� ��������:
	// ����� �� ��������� ���������� ���������� fixedPoint ����� ��������?
	void RotateAroundXY(float angle, const Vector4f &fixedPoint);

	// ����� �������������� �� ����������� (shift > 0) ��� ������ ����������� �������
	void Shift(float shift);

	// ���������� �������� ����� �� ���������� ������� ��������� ��������������
	// ������� ��������� �������������� ���, ��� ������� ��������� ����������
	// ������ {1, 0, 0, 0}, � ������� x-, y-, z-���������� ����� � ���������� ������� 
	virtual Ogre::Vector3 GetInnerCoordinates(const Vector4f &point) const;
	// �������� �������� ����������: ��������� ���������� ��������� �����, �������  
	// �� ���������, �� ���������� �����������
	virtual Vector4f GetGlobalCoordinates(const Ogre::Vector3 &innerPoint) const;
private:
};

#endif // __FixedXYHyperPlane_h_