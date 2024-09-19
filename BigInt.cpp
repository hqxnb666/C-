#include"BigInt.h"
#include<cassert>
//#include <tuple>

int BigInt::base_char=8;
int BigInt::base=0xFFFFFFFF;
int BigInt::basebit=5;//2^5
int BigInt::basebitchar=0x1F;
int BigInt::basebitnum=32;
BigInt BigInt::Zero(0);
BigInt BigInt::One(1);
BigInt BigInt::Two(2);



//// Montgomery multiplication
//BigInt BigInt::montgomeryMultiply(const BigInt& a, const BigInt& b, const BigInt& n, const BigInt& nPrime, const BigInt& R) const {
//	BigInt t = a * b;
//	BigInt m = (t * nPrime) & (R - 1);
//	BigInt u = (t + m * n) >> R.bitLength();
//	if (u >= n) {
//		u = u - n;
//	}
//	return u;
//}




BigInt BigInt::random(int length) {
	BigInt result;
	result._data.clear();
	for (int i = 0; i < length; ++i) {
		result._data.push_back(static_cast<base_t>(rand()));
	}
	return result;
}

BigInt operator + (const BigInt& a,const BigInt& b)
{
	BigInt ca(a);
	return ca.add(b);
}

BigInt operator - (const BigInt& a,const BigInt& b)
{
	BigInt ca(a);
	return ca.sub(b);
}



//BigInt operator * (const BigInt& a,const BigInt& b)
//{
//	if(a==(BigInt::Zero) || b==(BigInt::Zero))
//		return BigInt::Zero;
//
//	const BigInt &big=a._data.size()>b._data.size()?a:b;
//	const BigInt &small=(&big)==(&a)?b:a;
//
//	BigInt result(0);
//	
//	BigInt::bit bt(small);
//	for(int i=bt.size()-1;i>=0;--i)
//	{
//		if(bt.at(i))
//		{
//			BigInt temp(big,false);
//			temp.leftShift(i);
//			//std::cout<<"tmp:"<<temp<<std::endl;
//			result.add(temp);
//			//std::cout<<"res:"<<result<<std::endl;
//		}
//	}
//	result._isnegative=!(a._isnegative==b._isnegative);
//	return result;
//}
BigInt BigInt::basicMultiply(const BigInt& x, const BigInt& y) const {
	BigInt result;
	result._data.resize(x._data.size() + y._data.size(), 0);

	for (size_t i = 0; i < x._data.size(); ++i) {
		uint64_t carry = 0;
		for (size_t j = 0; j < y._data.size(); ++j) {
			uint64_t temp = static_cast<uint64_t>(x._data[i]) * y._data[j] + result._data[i + j] + carry;
			result._data[i + j] = static_cast<uint32_t>(temp & 0xFFFFFFFF);  // 显式转换
			carry = temp >> 32;
		}
		result._data[i + y._data.size()] = static_cast<uint32_t>(carry);  // 显式转换
	}


	return result.trim();
}

BigInt BigInt::karatsubaMultiply(const BigInt& x, const BigInt& y) const {
	// 设置一个阈值，小于该值时使用普通乘法
	const size_t THRESHOLD = 32;

	if (x._data.size() < THRESHOLD || y._data.size() < THRESHOLD) {
		return basicMultiply(x, y); // 使用基础乘法
	}


	if (x._data.size() == 1 && y._data.size() == 1) {
		return BigInt(static_cast<long>(x._data[0]) * static_cast<long>(y._data[0]));
	}

	size_t n = std::max(x._data.size(), y._data.size());
	size_t half = (n + 1) / 2;

	BigInt x0, x1, y0, y1;

	x0._data.assign(x._data.begin(), x._data.begin() + std::min(half, x._data.size()));
	if (x._data.size() > half) {
		x1._data.assign(x._data.begin() + half, x._data.end());
	}

	y0._data.assign(y._data.begin(), y._data.begin() + std::min(half, y._data.size()));
	if (y._data.size() > half) {
		y1._data.assign(y._data.begin() + half, y._data.end());
	}

	BigInt z0 = karatsubaMultiply(x0, y0);
	BigInt z2 = karatsubaMultiply(x1, y1);
	BigInt z1 = karatsubaMultiply(x0 + x1, y0 + y1) - z0 - z2;

	BigInt result = (z2.leftShift(2 * half * BigInt::basebit)) + (z1.leftShift(half * BigInt::basebit)) + z0;
	return result.trim();
}



BigInt operator*(const BigInt& a, const BigInt& b) {
	if (a == BigInt::Zero || b == BigInt::Zero) {
		return BigInt::Zero;
	}

	BigInt result = a.karatsubaMultiply(a, b);
	result._isnegative = !(a._isnegative == b._isnegative);

	return result;
}










BigInt operator / (const BigInt& a,const BigInt& b)
{
	assert(b!=(BigInt::Zero));
	if(a.equals(b))//绝对值相等
		return (a._isnegative==b._isnegative)?BigInt(1):BigInt(-1);
	else if(a.smallThan(b))//绝对值小于
		return BigInt::Zero;
	else
	{
		BigInt result,ca;
		BigInt::div(a,b,result,ca);
		return result;
	}
}

BigInt operator % (const BigInt& a,const BigInt& b)
{
	assert(b!=(BigInt::Zero));
	if (a.equals(b))
		return BigInt::Zero;
	else if (a.smallThan(b))
		return a;
	else
	{
		BigInt result,ca;
		
		BigInt::div(a,b,result,ca);
		//std::cout << "444444" << std::endl;
		return ca;
	}
}

void BigInt::div(const BigInt& a,const BigInt& b,BigInt& result,BigInt& ca)
{
	//1.复制a,b
	BigInt cb(b,false);
	ca._isnegative=false;
	ca._data=a._data;

	BigInt::bit bit_b(cb);
	//位数对齐
	while(true)//绝对值小于
	{
		BigInt::bit bit_a(ca);
		int len=bit_a.size()-bit_b.size();
		BigInt temp;
		//找到移位的
		while(len>=0)
		{
			temp=cb<<len;
			if(temp.smallOrEquals(ca))
				break;
			--len;
		}
		if(len<0)
			break;
		BigInt::base_t n=0;
		while(temp.smallOrEquals(ca))
		{
			ca.sub(temp);
			++n;
		}
		BigInt kk(n);
		if(len)
			kk.leftShift(len);
		result.add(kk);
	}
	result.trim();
}

bool operator < (const BigInt& a,const BigInt& b)
{
	if(a._isnegative==b._isnegative)
	{
		if(a._isnegative==false)
			return a.smallThan(b);
		else
			return !(a.smallOrEquals(b));
	}
	else
	{
		if(a._isnegative==false)
			return true;
		else
			return false;
	}
}

bool operator <= (const BigInt& a,const BigInt& b)
{
	if(a._isnegative==b._isnegative)
	{//同号
		if(a._isnegative==false)
			return a.smallOrEquals(b);
		else
			return !(a.smallThan(b));
	}
	else//异号
	{
		if(a._isnegative==false)
			return true;
		else
			return false;
	}
}

bool operator == (const BigInt& a,const BigInt& b)
{
	return a._data==b._data && a._isnegative == b._isnegative;
}

ostream& operator << (ostream& out,const BigInt& a)
{
	static char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	if(a._isnegative)
		out<<"-";
	BigInt::base_t T=0x0F;
	std::string str;
	for(BigInt::data_t::const_iterator it=a._data.begin();it!=a._data.end();++it)
	{
		BigInt::base_t ch=(*it);
		for(int j=0;j<BigInt::base_char;++j)
		{
			str.push_back(hex[ch&(T)]);
			ch=ch>>4;
		}
	}
	reverse(str.begin(),str.end());
	out<<str;
	return out;
}

BigInt operator <<(const BigInt& a,unsigned int n)
{
	BigInt ca(a);
	return ca.leftShift(n);
}

BigInt& BigInt::leftShift(const unsigned int n)
{
	int k=n>>(BigInt::basebit);//5
	int off=n&(BigInt::basebitchar);//0xFF

	int inc=(off==0)?k:1+k;
	for(int i=0;i<inc;++i)
		_data.push_back(0);

	if(k)
	{
		inc=(off==0)?1:2;
		for(int i=_data.size()-inc;i>=k;--i)
			_data[i]=_data[i-k];
		for(int i=0;i<k;++i)
			_data[i]=0;
	}

	if(off)
	{
		BigInt::base_t T=BigInt::base;//0xffffffff
		T=T<<(BigInt::basebitnum-off);//32
		//左移
		BigInt::base_t ch=0;
		for(std::size_t i=0;i<_data.size();++i)
		{
			BigInt::base_t t=_data[i];
			_data[i]=(t<<off)|ch;
			ch=(t&T)>>(BigInt::basebitnum-off);//32,最高位
		}
	}
	trim();
	return *this;
}

BigInt& BigInt::rightShift(const unsigned int n)
{
	int k=n>>(BigInt::basebit);//5
	int off=n&(BigInt::basebitchar);//0xFF

	if(k)
	{
		for(int i=0;i>k;++i)
			_data[i]=_data[i+k];
		for(int i=0;i<k;++i)
			_data.pop_back();
		if(_data.size()==0)
			_data.push_back(0);
	}

	if(off)
	{
		BigInt::base_t T=BigInt::base;//0xFFFFFFFF
		T=T>>(BigInt::basebitnum-off);//32
		//左移
		BigInt::base_t ch=0;
		for(int i=_data.size()-1;i>=0;--i)
		{
			BigInt::base_t t=_data[i];
			_data[i]=(t>>off)|ch;
			ch=(t&T)<<(BigInt::basebitnum-off);//32,最高位
		}
	}
	trim();
	return *this;
}

BigInt& BigInt::sub(const BigInt& b)
{
	if(b._isnegative==_isnegative)
	{//同号
		
		BigInt::data_t &res=_data;
		if(!(smallThan(b)))//绝对值大于b
		{
			int cn=0;//借位
			//大数减小数
			for(std::size_t i=0;i<b._data.size();++i)
			{
				BigInt::base_t temp=res[i];
				res[i]=(res[i]-b._data[i]-cn);
				cn=temp<res[i]?1:temp<b._data[i]?1:0;
			}

			for(std::size_t i=b._data.size();i<_data.size() && cn!=0;++i)
			{
				BigInt::base_t temp=res[i];
				res[i]=res[i]-cn;
				cn=temp<cn;
			}
			trim();
		}
		else//绝对值小于b
		{
			_data=(b-(*this))._data;
			_isnegative=!_isnegative;
		}
	}
	else
	{//异号的情况
		bool isnegative=_isnegative;
		_isnegative=b._isnegative;
		add(b);
		_isnegative=isnegative;
	}
	return *this;
}

BigInt& BigInt::add(const BigInt& b)
{
	if(_isnegative==b._isnegative)
	{//同号
		//引用
		BigInt::data_t &res=_data;
		int len=b._data.size()-_data.size();

		while((len--)>0)//高位补0
			res.push_back(0);

		int cn=0;//进位
		for(std::size_t i=0;i<b._data.size();++i)
		{
			BigInt::base_t temp=res[i];
			res[i]=res[i]+b._data[i]+cn;
			cn=temp>res[i]?1:temp>(temp+b._data[i])?1:0;//0xFFFFFFFF
		}

		for(std::size_t i=b._data.size();i<_data.size() && cn!=0;++i)
		{
			BigInt::base_t temp=res[i];
			res[i]=(res[i]+cn);
			cn=temp>res[i];
		}

		if(cn!=0)
			res.push_back(cn);
		
		trim();
	}
	else
	{//异号的情况
		bool isnegative;
		if(smallThan(b))//绝对值小于b
			isnegative=b._isnegative;
		else if(equals(b))//绝对值等于b
			isnegative=false;
		else//绝对值大于b
			isnegative=_isnegative;

		_isnegative=b._isnegative;
		sub(b);
		_isnegative=isnegative;		
	}
	return *this;
}


//// 蒙哥马利还原
//BigInt BigInt::montgomery_reduce(const BigInt& t, const BigInt& n, const BigInt& n_prime, int r_bits) const {
//	BigInt m = (t * n_prime) & ((BigInt(1) << r_bits) - 1);
//	BigInt u = (t + m * n) >> r_bits;
//	if (u >= n) {
//		u = u - n;
//	}
//	return u;
//}
//
//// 蒙哥马利乘法
//BigInt BigInt::montgomery_mul(const BigInt& a, const BigInt& b, const BigInt& n, const BigInt& n_prime, int r_bits) const {
//	BigInt t = a * b;
//	return montgomery_reduce(t, n, n_prime, r_bits);
//}
//
//// 蒙哥马利模幂运算
//BigInt BigInt::moden(const BigInt& exp, const BigInt& p) const {
//	int r_bits = p.bitLength();
//	BigInt r = BigInt(1) << r_bits; // R = 2^r_bits
//	BigInt r_inv = r.modInverse(p); // R^-1 mod p
//	BigInt n_prime = (r - p.modInverse(r)) & ((BigInt(1) << r_bits) - 1); // -n^(-1) mod R
//	BigInt x = (*this * r) % p; // X = x * R mod p
//	BigInt result = (BigInt(1) * r) % p; // R = R mod p
//
//	for (int i = exp.bitLength() - 1; i >= 0; --i) {
//		result = montgomery_mul(result, result, p, n_prime, r_bits);
//		if (exp.at(i)) {
//			result = montgomery_mul(result, x, p, n_prime, r_bits);
//		}
//	}
//
//	result = montgomery_reduce(result, p, n_prime, r_bits);
//	return result;
//}
//
//
//void BigInt::removeLeadingZeros() {
//	while (!digits.empty() && digits.back() == 0) {
//		digits.pop_back();
//	}
//}
//
//bool BigInt::operator>=(const BigInt& other) const {
//	return !(*this < other);
//}
//
//bool BigInt::operator>(const BigInt& other) const {
//	return other < *this;
//}
//
//// 按位与运算的实现
//BigInt BigInt::operator&(const BigInt& other) const {
//	BigInt result;
//	result.digits.resize(std::min(digits.size(), other.digits.size()));
//
//	for (size_t i = 0; i < result.digits.size(); ++i) {
//		result.digits[i] = digits[i] & other.digits[i];
//	}
//
//	result.removeLeadingZeros();
//	return result;
//}
//
//// 右移运算的实现
//BigInt BigInt::operator>>(int shift) const {
//	BigInt result(*this);
//	int word_shift = shift / 32;
//	int bit_shift = shift % 32;
//
//	for (size_t i = 0; i < result.digits.size(); ++i) {
//		if (i + word_shift < result.digits.size()) {
//			result.digits[i] = result.digits[i + word_shift] >> bit_shift;
//			if (i + word_shift + 1 < result.digits.size()) {
//				result.digits[i] |= result.digits[i + word_shift + 1] << (32 - bit_shift);
//			}
//		}
//		else {
//			result.digits[i] = 0;
//		}
//	}
//
//	result.removeLeadingZeros();
//	return result;
//}
//
//// 返回二进制位长度
//int BigInt::bitLength() const {
//	if (digits.empty()) {
//		return 0;
//	}
//
//	int bits = (digits.size() - 1) * 32;
//	uint32_t most_significant_digit = digits.back();
//
//	while (most_significant_digit > 0) {
//		most_significant_digit >>= 1;
//		++bits;
//	}
//
//	return bits;
//}
//
//// 返回某个二进制位
//bool BigInt::at(int index) const {
//	int word_index = index / 32;
//	int bit_index = index % 32;
//
//	if (word_index >= digits.size()) {
//		return false;
//	}
//
//	return (digits[word_index] & (1 << bit_index)) != 0;
//}
//
//// 求模逆
//BigInt BigInt::modInverse(const BigInt& mod) const {
//	BigInt a = *this, b = mod;
//	BigInt x0(0), x1(1);
//
//	while (a > 1) {
//		BigInt q = a / b;
//		BigInt temp = b;
//		b = a % b;
//		a = temp;
//
//		temp = x0;
//		x0 = x1 - q * x0;
//		x1 = temp;
//	}
//
//	if (x1 < 0) {
//		x1 = x1 + mod;
//	}
//
//	return x1;
//}


// 运算符 += 的实现
BigInt& BigInt::operator+=(const BigInt& rhs) {
	// 实现加法逻辑
	// 假设 BigInt 提供了 add 函数来处理加法
	this->add(rhs);
	return *this;
}


//BigInt BigInt::moden(const BigInt& exp, const BigInt& p) const {
//	BigInt::bit t(exp);
//
//	BigInt d(1);
//	// 从指数的最高位开始向低位迭代
//	for (int i = t.size() - 1; i >= 0; --i) {
//		// 将结果平方
//		d = (d * d) % p;
//		// 如果当前位为 1，则乘以底数（模 p）
//		if (t.at(i)) {
//			d = (d * (*this)) % p;
//		}
//	}
//	return d;
//}

BigInt BigInt::moden(const BigInt& exp, const BigInt& p) const {
	BigInt::bit t(exp);

	BigInt d(1);
	for (int i = t.size() - 1; i >= 0; --i) {
		d = (d * d) % p;
		//std::cout << "After squaring: d = " << d << std::endl;
		if (t.at(i)) {
			d = (d * (*this)) % p;
			//std::cout << "After multiplying: d = " << d << std::endl;
		}
	}
	return d;
}




BigInt BigInt::extendEuclid(const BigInt& m) {
	assert(m._isnegative == false); // m为正数
	BigInt a[3], b[3], t[3];
	a[0] = 1; a[1] = 0; a[2] = m;
	b[0] = 0; b[1] = 1; b[2] = *this;
	if (b[2] == BigInt::Zero || b[2] == BigInt::One)
		return b[2];

	while (true) {
		if (b[2] == BigInt::One) {
			if (b[1]._isnegative == true) // 负数
				b[1] = (b[1] % m + m) % m;
			return b[1];
		}

		BigInt q = a[2] / b[2];
		for (int i = 0; i < 3; ++i) {
			t[i] = a[i] - q * b[i];
			a[i] = b[i];
			b[i] = t[i];
		}
	}
}


std::size_t BigInt::bit::size()
{
	return _size;
}

bool BigInt::bit::at(std::size_t i)
{
	std::size_t index=i>>(BigInt::basebit);
	std::size_t off=i&(BigInt::basebitchar);
	BigInt::base_t t=_bitvec[index];
	return (t&(1<<off));
}

BigInt::bit::bit(const BigInt& ba)
{
	_bitvec=ba._data;
	BigInt::base_t a=_bitvec[_bitvec.size()-1];//最高位
	_size=_bitvec.size()<<(BigInt::basebit);
	BigInt::base_t t=1<<(BigInt::basebitnum-1);
	
	if(a==0)
		_size-=(BigInt::basebitnum);
	else
	{
		while(!(a&t))
		{
			--_size;
			t=t>>1;
		}
	}
}

bool BigInt::smallThan(const BigInt& b)const
{
	if(_data.size()==b._data.size())
	{
		for(BigInt::data_t::const_reverse_iterator it=_data.rbegin(),it_b=b._data.rbegin();
			it!=_data.rend();++it,++it_b)
			if((*it)!=(*it_b))
				return (*it)<(*it_b);
		return false;//相等
	}
	else
		return _data.size()<b._data.size();
}

bool BigInt::smallOrEquals(const BigInt& b)const
{
	if(_data.size()==b._data.size())
	{
		for(BigInt::data_t::const_reverse_iterator it=_data.rbegin(),it_b=b._data.rbegin();
			it!=_data.rend();++it,++it_b)
			if((*it)!=(*it_b))
				return (*it)<(*it_b);
		return true;//相等
	}
	else
		return _data.size()<b._data.size();
}

bool BigInt::equals(const BigInt& a)const
{
	return _data==a._data;
}