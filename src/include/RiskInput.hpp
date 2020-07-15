#ifndef __RISKINPUT_HPP_
#define __RISKINPUT_HPP_

class RiskInput
{
public:
    RiskInput();
    RiskInput(RiskInput &&) = default;
    RiskInput(const RiskInput &) = default;
    RiskInput &operator=(RiskInput &&) = default;
    RiskInput &operator=(const RiskInput &) = default;
    ~RiskInput();

private:
    
};

RiskInput::RiskInput()
{
}

RiskInput::~RiskInput()
{
}

#endif // !__RISKINPUT_HPP_