#include "DataActor.h"

static inline double Mix(double smallVar, double bigVar, double x) {	//�����ֵ
	return x * (bigVar - smallVar) + smallVar;
}

void Dmsl::DataActor::Update() {
	for (auto& p : m_datas) {
		++p.timer;

		//TODO:�޸Ĵ��д��룬�����޸Ĳ�ֵ����
		*p.data = Mix(p.start, p.end, double(p.timer) / p.len);
	}
	auto nend = std::remove_if(m_datas.begin(), m_datas.end(), [](const Data& i) {
		return i.timer >= i.len;
	});
	m_datas.erase(nend, m_datas.end());
}
