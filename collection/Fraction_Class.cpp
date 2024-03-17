struct fraction {
	long long a, b;

	fraction() {
		a = b = 0;
	}

	fraction(long long aa, long long bb) {
		if (!bb)
			a = 1, b = 0;
		else if (!aa)
			a = 0, b = 1;
		else {
			long long g = __gcd(abs(aa), abs(bb));
			aa /= g, bb /= g;
			if (bb < 0)
				aa *= -1, bb *= -1;
			a = aa, b = bb;
		}
	}

	const bool operator <(const fraction& rhs) const {
		return a * rhs.b < b * rhs.a;
	}

	const bool operator ==(const fraction& rhs) const {
		return !(*this < rhs) && !(rhs < *this);
	}

	const bool operator <=(const fraction& rhs) const {
		return !(rhs < *this);
	}

	const bool operator !=(const fraction& rhs) const {
		return *this < rhs || rhs < *this;
	}

	fraction& operator =(const fraction& rhs) {
		a = rhs.a, b = rhs.b;
		return *this;
	}

	fraction operator +(const fraction& rhs) const {
		return fraction(a * rhs.b + b * rhs.a, b * rhs.b);
	}

	fraction& operator +=(const fraction& rhs) {
		return *this = *this + rhs;
	}

	fraction operator -(const fraction& rhs) const {
		return fraction(a * rhs.b - b * rhs.a, b * rhs.b);
	}

	fraction& operator -=(const fraction& rhs) {
		return *this = *this - rhs;
	}

	fraction operator *(const fraction& rhs) const {
		return fraction(a * rhs.a, b * rhs.b);
	}

	fraction& operator *=(const fraction& rhs) {
		return *this = *this * rhs;
	}

	fraction operator /(const fraction& rhs) const {
		return fraction(a * rhs.b, b * rhs.a);
	}

	fraction& operator /=(const fraction& rhs) {
		return *this = *this / rhs;
	}
};
