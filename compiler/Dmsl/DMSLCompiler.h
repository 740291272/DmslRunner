#pragma once
#include <map>
#include <vector>
#include <string>
#include <stack>
#include "DMSLPrecompiler.h"
#include "DMSLElf.h"
#include "Dmsl.h"

namespace Dmsl {
	namespace Compiler {
		/*struct Compiled {
			struct Unit {
				uint32_t memSize;
				std::vector<uint8_t> initProgram, mainProgram;
			};
			std::map<std::string, uint32_t> linkTable;
			std::map<uint32_t,uint32_t> metParamNum,funcParamNum;
			std::map<uint32_t, Unit> units;
			uint32_t uniformSize,cFuncSize,cMetSize;
		};*/

		//���룬�ɹ��򷵻�true
		bool Compile(const Precompiled& in, Compiled& out,std::ostream& log);

		//�������Ԫ
		void CompileUnit(const Dmsl::Compiler::Precompiled& in,const Precompiled::Unit&,std::vector<uint8_t>& out,const std::vector<Precompiled::Unit::Code>& inProgram);

		//���б���
		void CompileLines(const Dmsl::Compiler::Precompiled& in,const Precompiled::Unit&,std::vector<uint8_t>& out,const std::vector<Precompiled::Unit::Code>& inProgram,uint32_t begin,uint32_t end);

		//��begin��ʼ����ͬһ��������¸���leftWord��ͬ�������䣬����������ʼ����Ͳ�������ֱ�ӷ���end���λ��
		uint32_t SearchSameLayerBlockCode(const std::vector<Precompiled::Unit::Code>& code,const std::string& leftWord,uint32_t begin);

		//��doubleѹ������
		void PushDouble(double, std::vector<uint8_t>& out);

		//�ѵ�ַѹ����룬����ѹ��ĵ�ַ�ĵ�ַ
		uintptr_t PushAddress(uintptr_t, std::vector<uint8_t>& out);

		//���ݶ�����ַ���������Ѿ���ѹ��ĵ�ַ
		void ResetAddress(uintptr_t addressSaddress, uintptr_t address, std::vector<uint8_t>& out);

		//��ָ��ѹ�����
		void PushCmd(Dmsl::VirtualMachine::ElfCode, std::vector<uint8_t>& out);

		//�������ı���ʽ�ṹ��
		struct ParsedMathWord final{
			enum {
				NUMBER, VARNAME, OPR, FUNC_NAME
			}type;
			bool nega = false;	//�෴��
			struct Data{
				std::string varName;
				double number;
				struct Opr{
					int level;	//���ȼ���¼
					enum {
						COMMA,	//1�����ȼ�
						AND,
						OR,
						NOT,	//2�����ȼ�
						NE,	//3�����ȼ�
						EQ,
						BIG,
						BIGE,
						SML,
						SMLE,
						ADD,	//4��
						SUB,
						MUL,	//5
						DIV,
						MOD,
						CALL_FUNC,	//7
						NEGA    //6
					}opr;	//������
					uint32_t funcAddress;
					//���������ţ����ȼ�+10��������-10
				}opr;
			}data;
		};

		//��������ʽ������
		//����ֵ���壺
		//0 - ����ʽ����1��Boolֵ
		//n(>=1) - ����ʽ����n��double
		int ParseMath(const Precompiled& in,const Precompiled::Unit& unit, std::string, std::vector<uint8_t>& out);

		//��������ʽ�²㺯�� -- ѹ��ɨ�赽������
		void ParseData(const Precompiled& in, const Precompiled::Unit& unit,const ParsedMathWord&, std::vector<uint8_t>& out,std::stack<int>& testStk);

		//��������ʽ�²㺯�� -- ѹ��ɨ�赽�Ĳ�����
		void ParseOperator(const Precompiled& in,const ParsedMathWord&, std::vector<uint8_t>& out,std::stack<ParsedMathWord::Data::Opr>& stk,std::stack<int>& testStk);

		//������д��������ջ
		void PopOprStack(std::stack<ParsedMathWord::Data::Opr>& stk,std::vector<uint8_t>& out,std::stack<int>& testStk,const Precompiled& in);

		//��ѯ��������
		//0 - ��֪��
		//1 - attribute
		//2 - unit::var
		//3 - uniform
		//4 - constant_define
		//5 - number
		//6 - cfunc
		//7 - cmethod
		//8 - inVarying
		//9 - outVarying
		int WhatsTheVar(const Precompiled& in,const Precompiled::Unit& unit, const std::string& name);

		//�ݹ鴦��if�ṹ
		void CompileIfLines(const Dmsl::Compiler::Precompiled& in,const Precompiled::Unit&,std::vector<uint8_t>& out,const std::vector<Precompiled::Unit::Code>& inProgram,uint32_t begin,uint32_t end);

		//����Times�ṹ
		void CompileTimesLines(const Dmsl::Compiler::Precompiled& in, const Precompiled::Unit&, std::vector<uint8_t>& out, const std::vector<Precompiled::Unit::Code>& inProgram, uint32_t begin, uint32_t end,int times);
	}
}
