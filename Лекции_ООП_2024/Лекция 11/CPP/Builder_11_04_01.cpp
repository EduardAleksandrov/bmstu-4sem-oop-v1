# include <iostream>
# include <memory>

using namespace std;

# pragma region Product
class Product
{
public:
	virtual ~Product() = default;

	virtual void run() = 0;
};

class ConProd1 : public Product
{
public:
	ConProd1() { cout << "Calling the ConProd1 constructor;" << endl; }
	~ConProd1() override { cout << "Calling the ConProd1 destructor;" << endl; }

	void run() override { cout << "Calling the run method;" << endl; }
};

# pragma endregion

# pragma region Builder
class Builder
{
public:
	virtual ~Builder() = default;

	virtual bool buildPart1() = 0;
	virtual bool buildPart2() = 0;

	shared_ptr<Product> getProduct();

protected:
	virtual shared_ptr<Product> createProduct() = 0;

	shared_ptr<Product> product{ nullptr };
	size_t part{ 0 };
};

class ConBuilder : public Builder
{
public:
	bool buildPart1() override
	{
		if (!part)
			++part;

		if (part != 1) return false;

		cout << "Completed part: " << part << ";" << endl;
		return true;
	}
	bool buildPart2() override
	{
		if (part == 1)
			++part;

		if (part != 2) return false;

		cout << "Completed part: " << part << ";" << endl;
		return true;
	}

protected:
	shared_ptr<Product> createProduct() override;
};

# pragma endregion

# pragma region Creator
class Creator
{
public:
	virtual ~Creator() = default;

	virtual shared_ptr<Product> create() = 0;
};

class Director : public Creator
{
public:
	Director(shared_ptr<Builder> builder) : br(builder) {}

	shared_ptr<Product> create() override
	{
		if (br->buildPart1() && br->buildPart2()) return br->getProduct();

		return nullptr;
	}

private:
	shared_ptr<Builder> br;
};

# pragma endregion

# pragma region Methods
shared_ptr<Product> Builder::getProduct()
{
	if (!product) { product = createProduct(); }

	return product;
}

shared_ptr<Product> ConBuilder::createProduct()
{
	if (part == 2) { product = make_shared<ConProd1>(); }

	return product;
}

# pragma endregion

class User
{
public:
	void use(shared_ptr<Creator>& cr)
	{
		shared_ptr<Product> prod = cr->create();

		if (prod)
			prod->run();
	}
};

int main()
{
	shared_ptr<Builder> builder = make_shared<ConBuilder>();
	shared_ptr<Creator> cr = make_shared<Director>(builder);

	User{}.use(cr);
}
