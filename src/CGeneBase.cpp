/******************************************************************************
**
** Copyright (C) 2019-2031 Dr.Gui-lin Zhuang <glzhuang@zjut.edu.cn>
** All rights reserved.
**
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/
#include "CGenebase.h"
#include "../Util/Bitset.h"
#include "../Util/log.hpp"
#include "GaUtilityFunction.h"
using namespace boost;
namespace GAZJUT{
CGenebase::CGenebase()
{
    this->m_VarRangeStruct=nullptr;
}
CGenebase::CGenebase(VarRangeStruct* var)
{
    //util::Log::Info<<"CGenebase::CGenebase(VarRangeStruct* var)!\n";
   // util::Log::Info<<var->size()<<std::endl;
    //util::Log::Info<<var->min<<" "<<var->max<<std::endl;

    this->init(var);
}
double CGenebase::decode()
{
    return this->m_value;
}
void CGenebase::init(VarRangeStruct* var)
{
    //util::Log::Info<<"CGenebase::init(VarRangeStruct* var)!\n";
    m_VarRangeStruct=var;
}
void CGenebase::updatecode(double m)
{

}
Bitset& CGenebase::bitGene()
{
    Bitset a1(4,BOOST_BINARY(0000));        // nothing is done!
    return a1;
}
double& CGenebase::realGene()
{
    return this->m_value;
}
double CGenebase::value()
{
    return this->m_value;
}
size_t CGenebase::bitNum()
{
    return 0;
}
CGenebase::~CGenebase()
{
    //delete this->m_VarRangeStruct;
}


}
