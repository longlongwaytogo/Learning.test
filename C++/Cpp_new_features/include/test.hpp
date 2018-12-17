
template Test
{
public:
    Test( )
    {
        std::cout << "start test:----------" << _name << "----------" << std::endl;
    }

    ~Test()
    {
        std::cout << "end test:----------" << _name << "----------" << std::endl;
    }

protected:
    std::string _name;
};

