/*
 * mathevaluation.cpp - Implementation of the MathEvaluation class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */

#include <rush/mathevaluation.h>
#include <rush/console.h>
#include <rush/parser.h>
#include <rush/stack.h>
#include "mathdefaultfunctions.h"
#include "mathvariable.h"


namespace rush {






//-----------------------------------------------------------------------------
MathEvaluation::MathEvaluation()
/**
 * \brief Constructor, initializes the MathEvaluation object.
 **/
{
    m_functions = new ObjectArray<MathFunction>();
    m_opcodes = new ObjectArray<MathOpcode>();
    m_variables = new ObjectArray<MathVariable>();
    m_errors = new StringArray();

    // Insert default functions
    m_functions->Add(new MathPiFunction());
    m_functions->Add(new MathAbsFunction());
    m_functions->Add(new MathExpFunction());
    m_functions->Add(new MathPowFunction());
    m_functions->Add(new MathSqrtFunction());
    m_functions->Add(new MathRootFunction());
    m_functions->Add(new MathLnFunction());
    m_functions->Add(new MathLog10Function());
    m_functions->Add(new MathLogFunction());
    m_functions->Add(new MathFactFunction());
    m_functions->Add(new MathModFunction());
    m_functions->Add(new MathCeilFunction());
    m_functions->Add(new MathFloorFunction());
    m_functions->Add(new MathFracFunction());
    m_functions->Add(new MathIntFunction());
    m_functions->Add(new MathSinFunction());
    m_functions->Add(new MathCosFunction());
    m_functions->Add(new MathTanFunction());
}


//-----------------------------------------------------------------------------
MathEvaluation::~MathEvaluation()
/**
 * \brief Destructor, frees allocated memory
 **/
{
    if (m_functions != NULL)
    {
        delete m_functions;
    }
    if (m_opcodes != NULL)
    {
        delete m_opcodes;
    }
    if (m_variables != NULL)
    {
        delete m_variables;
    }
    if (m_errors != NULL)
    {
        delete m_errors;
    }
}


//-----------------------------------------------------------------------------
void MathEvaluation::SetVariable(const String& name, double value)
/**
 * \brief Sets the value of a variable in this instance. The variable
 * does not have to exist in the expression. The variable name is case-sensitive.
 * \param name Variable name.
 * \param value Variable value.
 **/
{
    // Search for the variable
    MathVariable* variable = NULL;
    for (size_t i=0; i<m_variables->Count(); ++i)
    {
        if (m_variables->Item(i)->GetName() == name)
        {
            variable = m_variables->Item(i);
            break;
        }
    }

    if (variable == NULL)
    {
        // Create the variable if it doesn't exist
        variable = new MathVariable(name, value);
        m_variables->Add(variable);
    }
    else
    {
        // Set the value
        variable->SetValue(value);
    }
}


//-----------------------------------------------------------------------------
double MathEvaluation::GetVariable(const String& name) const
/**
 * \brief Gets the value of a variable in this instance. An error is generated if
 * the requesting variable does not exist. The variable name is case-sensitive.
 * \param name Variable name.
 * \return Variable value.
 **/
{
    // Search for the variable
    MathVariable* variable = NULL;
    for (size_t i=0; i<m_variables->Count(); ++i)
    {
        if (m_variables->Item(i)->GetName() == name)
        {
            variable = m_variables->Item(i);
            break;
        }
    }

    // Handle undefined variable
    if (variable == NULL)
    {
        m_errors->Add(String::Format(_T("Variable '%s' does not exist."), name.c_str()));
        return (0.0d);
    }
    return (variable->GetValue());
}



//-----------------------------------------------------------------------------
void MathEvaluation::ClearVariables()
/**
 * \brief Removes all variables from this class.
 **/
{
    m_variables->Clear();
}



//-----------------------------------------------------------------------------
StringArray* MathEvaluation::GetVariableNames() const
/**
 * \brief Returns all variable names of the currently available variables.
 * Note that the retuned StringArray must be deleted after usage.
 * \return StringArray with variable names (never null).
 **/
{
    StringArray* array = new StringArray(m_variables->Count());
    for (size_t i=0; i<m_variables->Count(); ++i)
    {
        array->Add(m_variables->Item(i)->GetName());
    }
    return (array);
}


//-----------------------------------------------------------------------------
void MathEvaluation::SetFunction(MathFunction* function)
/**
 * \brief Sets the function to the evaluator. This method can override existing
 * functions, if their name is the same.
 * \param function Function.
 **/
{
    // Argument check
    if (function == NULL)
    {
        return;
    }

    // Check if function exists
    int index = -1;
    for (size_t i=0; i<m_functions->Count(); ++i)
    {
        if (m_functions->Item(i)->GetName() == function->GetName())
        {
            index = i;
            break;
        }
    }

    // Remove existing function
    if (index >= 0)
    {
        m_functions->Remove(index);
    }

    // Add function
    m_functions->Add(function);
}


//-----------------------------------------------------------------------------
bool MathEvaluation::HasErrors() const
/**
 * \brief Checks if errors are stored within this object.
 * \return True, if contains errors; otherwise false.
 **/
{
    return (m_errors->Count() != 0);
}


//-----------------------------------------------------------------------------
String MathEvaluation::GetErrorMessage() const
/**
 * \brief Returns the oldest error message and removes it from the errors
 * list. This method returns a empty string, if there are no more errors.
 * You could also use this method in conjunction with the HasErrors() method.
 * \return Oldest error message or a empty string.
 **/
{
    if (m_errors->Count() > 0)
    {
        String message = m_errors->Item(0);
        m_errors->Remove(0);
        return (message);
    }
    return (_T(""));
}




//-----------------------------------------------------------------------------
int FindClosingBracket(ObjectArray<MathToken>* tokens, int openingIndex)
/**
 * \brief
 **/
{
    int depth = 1;
    for (size_t i=openingIndex+1; i<tokens->Count(); ++i)
    {
        MathToken* token = tokens->Item(i);
        if (token->GetType() == MathTokenType::Bracket)
        {
            if (token->GetContent() == _T("("))
            {
                depth += 1;
            }
            else if (token->GetContent() == _T(")"))
            {
                depth -= 1;
                if (depth == 0) return (i);
            }
        }
    }
    return (-1);
}


//-----------------------------------------------------------------------------
bool FindFunctionParts(ObjectArray<MathToken>* tokens, int openingIndex,
                       size_t* argsIndices, size_t maxArgs)
/**
 * \brief
 **/
{
    size_t argsCounter = 0;
    int depth = 0;
    for (size_t i=openingIndex+1; i<tokens->Count(); ++i)
    {
        MathToken* token = tokens->Item(i);
        if (token->GetType() == MathTokenType::Bracket)
        {
            if (token->GetContent() == _T("("))
            {
                depth += 1;
            }
            else if (token->GetContent() == _T(")"))
            {
                depth -= 1;
                if (depth < 0)
                {
                    // No arguments
                    if (maxArgs == 0 && argsCounter == 0) {
                        return (true);
                    }
                    // One or more arguments
                    if (maxArgs-1 == argsCounter) {
                        argsIndices[argsCounter] = i;
                        return (true);
                    } else {
                        return (false);
                    }
                }
            }
        }
        else if (token->GetType() == MathTokenType::Comma)
        {
            if (depth == 0)
            {
                argsIndices[argsCounter] = i;
                argsCounter++;
                if (argsCounter == maxArgs)
                {
                    return (false);
                }
            }
        }
    }
    return (false);
}







//-----------------------------------------------------------------------------
bool MathEvaluation::Compile(const String& statements)
/**
 * \brief Compiles the given statement into the internal intermediate language
 * and stores it in this instance. After compiling the statement it can be
 * quickly executed by calling the Execute() method.
 * \param statements Mathematical statements
 * \return True, if no errors available; otherwise false.
 **/
{
    // Clear old stuff
    m_opcodes->Clear();

    // Create tokens
    MathTokenizer tokenizer;
    if (!tokenizer.Parse(statements, m_errors))
    {
        return (false);
    }

    ObjectArray<MathToken>* tokens = tokenizer.GetTokens();
    if (tokens->Count() > 0)
    {
        MathOpcodeArray* opcodes = this->CompileStep(tokens, 0, tokens->Count()-1);
        m_opcodes->AddRange(opcodes, true);
        delete opcodes;
        this->OptimizeCode();
    }
    return (m_errors->Count() == 0);
}


//-----------------------------------------------------------------------------
bool MathEvaluation::Execute()
/**
 * \brief Executes the previously compiled intermediate language code.
 * You can execute the compiled statement multible times very fast, while
 * changing the variables.
 * \return True, if no errors available; otherwise false.
 **/
{
    Stack<double>* stack = new Stack<double>(128);
    for (size_t i=0; i<m_opcodes->Count(); ++i)
    {
        MathOpcode* opcode = m_opcodes->Item(i);
        if (opcode == NULL) {
            m_errors->Add(_T("Trying to execute bad code."));
            break;
        }
        if (opcode->GetType() == MathOpcodeType::Add)
        {
            if (stack->Count() < 2) {
                m_errors->Add(_T("At least two values needed for an ADD operation."));
            } else {
                stack->Push(stack->Pop() + stack->Pop());
            }
        }
        else if (opcode->GetType() == MathOpcodeType::CallFunction)
        {
            size_t index = opcode->GetIndex();
            if (index >= m_functions->Count()) {
                m_errors->Add(String::Format(_T("Cannot find function at index '%i', because it does not exist."), index));
            } else {
                MathFunction* function = m_functions->Item(index);
                size_t countArgs = function->GetArgs();
                if (stack->Count() < countArgs) {
                    m_errors->Add(String::Format(_T("At least '%u' values needed for the CALL operation."), countArgs));
                } else {
                    double values[countArgs];
                    for (int i=countArgs-1; i>=0; --i)
                    {
                        values[i] = stack->Pop();
                    }
                    stack->Push(function->Evaluate(values, countArgs));
                }
            }
        }
        else if (opcode->GetType() == MathOpcodeType::Div)
        {
            if (stack->Count() < 2) {
                m_errors->Add(_T("At least two values needed for an DIV operation."));
            } else {
                double temp = stack->Pop();
                stack->Push(stack->Pop() / temp);
            }
        }
        else if (opcode->GetType() == MathOpcodeType::Double)
        {
            if (stack->Count() < 1) {
                m_errors->Add(_T("At least one value needed for an DBL operation."));
            } else {
                double value = stack->Pop();
                stack->Push(value);
                stack->Push(value);
            }
        }
        else if (opcode->GetType() == MathOpcodeType::LoadConstant)
        {
            stack->Push(opcode->GetValue());
        }
        else if (opcode->GetType() == MathOpcodeType::LoadVariable)
        {
            size_t index = opcode->GetIndex();
            if (index >= m_variables->Count()) {
                m_errors->Add(String::Format(_T("Cannot load variable at index '%i', because it does not exist."), index));
            } else {
                MathVariable* variable = m_variables->Item(index);
                stack->Push(variable->GetValue());
            }
        }
        else if (opcode->GetType() == MathOpcodeType::Mul)
        {
            if (stack->Count() < 2) {
                m_errors->Add(_T("At least two values needed for an MUL operation."));
            } else {
                stack->Push(stack->Pop() * stack->Pop());
            }
        }
        else if (opcode->GetType() == MathOpcodeType::Neg)
        {
            if (stack->Count() < 1) {
                m_errors->Add(_T("At least one value needed for an NEG operation."));
            } else {
                stack->Push(-stack->Pop());
            }
        }
        else if (opcode->GetType() == MathOpcodeType::Nop)
        {
        }
        else if (opcode->GetType() == MathOpcodeType::SaveVariable)
        {
            size_t index = opcode->GetIndex();
            if (index >= m_variables->Count()) {
                m_errors->Add(String::Format(_T("Cannot save variable at index '%i', because it does not exist."), index));
            } else {
                if (stack->Count() < 1) {
                    m_errors->Add(_T("At least one value needed for an SAV operation."));
                } else {
                    MathVariable* variable = m_variables->Item(index);
                    variable->SetValue(stack->Pop());
                }
            }
        }
        else if (opcode->GetType() == MathOpcodeType::Sub)
        {
            if (stack->Count() < 2) {
                m_errors->Add(_T("At least two values needed for an SUB operation."));
            } else {
                double temp = stack->Pop();
                stack->Push(stack->Pop() - temp);
            }
        }
        else
        {
            m_errors->Add(_T("Unknown opcode."));
        }
    }
    delete stack;
    return (m_errors->Count() == 0);
}



#ifdef _RUSH_DEBUG_
//-----------------------------------------------------------------------------
String MathEvaluation::GetTokenizerText(const String& statements) const
/**
 * \brief
 **/
{
    String tokenizerText = _T("");

    // Parse statements
    MathTokenizer tokenizer;
    if (!tokenizer.Parse(statements, m_errors))
    {
        tokenizerText.Append(_T("Parser error: "));
    }

    // Rebuild text
    MathTokenArray* tokens = tokenizer.GetTokens();
    for (size_t i=0; i<tokens->Count(); ++i)
    {
        tokenizerText.AppendFormat(_T("%s "), tokens->Item(i)->ToString().c_str());
    }
    return (tokenizerText);
}
#endif


#ifdef _RUSH_DEBUG_
//-----------------------------------------------------------------------------
String MathEvaluation::GetOpcodeText() const
/**
 * \brief
 **/
{
    String opcodeText;
    for (size_t i=0; i<m_opcodes->Count(); ++i)
    {
        MathOpcode* opcode = m_opcodes->Item(i);
        if (opcode == NULL) {
            opcodeText.Append((_T("NULL ")));
            continue;
        }
        if (opcode->GetType() == MathOpcodeType::Add)
        {
            opcodeText.Append(_T("ADD "));
        }
        else if (opcode->GetType() == MathOpcodeType::CallFunction)
        {
            opcodeText.AppendFormat(_T("CALL '%s' "),
                m_functions->Item(opcode->GetIndex())->GetName().c_str());
        }
        else if (opcode->GetType() == MathOpcodeType::Div)
        {
            opcodeText.AppendFormat(_T("DIV "));
        }
        else if (opcode->GetType() == MathOpcodeType::Double)
        {
            opcodeText.AppendFormat(_T("DBL "));
        }
        else if (opcode->GetType() == MathOpcodeType::LoadConstant)
        {
            opcodeText.AppendFormat(_T("LDC '%1.2f' "), opcode->GetValue());
        }
        else if (opcode->GetType() == MathOpcodeType::LoadVariable)
        {
            opcodeText.AppendFormat(_T("LDV '%s' "),
                m_variables->Item(opcode->GetIndex())->GetName().c_str());
        }
        else if (opcode->GetType() == MathOpcodeType::Mul)
        {
            opcodeText.AppendFormat(_T("MUL "));
        }
        else if (opcode->GetType() == MathOpcodeType::Neg)
        {
            opcodeText.AppendFormat(_T("NEG "));
        }
        else if (opcode->GetType() == MathOpcodeType::Nop)
        {
            opcodeText.AppendFormat(_T("NOP "));
        }
        else if (opcode->GetType() == MathOpcodeType::SaveVariable)
        {
            opcodeText.AppendFormat(_T("SAV '%s' "),
                m_variables->Item(opcode->GetIndex())->GetName().c_str());
        }
        else if (opcode->GetType() == MathOpcodeType::Sub)
        {
            opcodeText.AppendFormat(_T("SUB "));
        }
        else if (opcode->GetType() == MathOpcodeType::Opcodes)
        {
            opcodeText.AppendFormat(_T("OPCODES '%u' "), opcode->GetArray()->Count());
        }
    }
    return (opcodeText);
}
#endif



//-----------------------------------------------------------------------------
bool MathEvaluation::HasHigherPriority(MathOpcodeType a, MathOpcodeType b)
/**
 * \brief Compares two opcodes and returns true, if opcode b has a higher priority
 * than opcode a.
 * \param a Type of opcode a.
 * \param b Type of opcode b.
 * \return True, when opcode b has a higher priority than a; otherwise false.
 **/
{
    return (((a == MathOpcodeType::Add || a == MathOpcodeType::Sub) &&
             (b == MathOpcodeType::Mul || b == MathOpcodeType::Div)) ||
             (b == MathOpcodeType::Neg && a != MathOpcodeType::Neg));
}



//-----------------------------------------------------------------------------
void MathEvaluation::PopInput(MathOpcodeArray* code, MathOpcodeDeque* inputs)
{
    MathOpcode* opcode = inputs->Pop();
    if (opcode == NULL)
    {
        m_errors->Add(_T("Internal error: Not enougth inputs available."));
    }
    else
    {
        if (opcode->GetType() == MathOpcodeType::Opcodes)
        {
            code->AddRange(opcode->GetArray(), true);
            delete opcode;
        }
        else
        {
            code->Add(opcode);
        }
    }
}



//-----------------------------------------------------------------------------
void MathEvaluation::ResolveOperator(MathOpcodeArray* code, MathOpcodeDeque* operators, MathOpcodeDeque* inputs, bool checkPriority)
/**
 * \brief Resolves the operators in the deque and writes the generated code sequenz into
 * the code array. Uses the input deque for the operands and differs the check of priority.
 * \param code Code array.
 * \param operators Operators deque.
 * \param inputs Inputs or operands deque.
 * \param checkPriority True, the enable Priority check; otherwise false.
 **/
{
    MathOpcode* opcode = operators->Pop();
    if (opcode->GetType() == MathOpcodeType::Add ||
        opcode->GetType() == MathOpcodeType::Sub ||
        opcode->GetType() == MathOpcodeType::Mul ||
        opcode->GetType() == MathOpcodeType::Div)
    {
        if (inputs->Count() < 2) {
            m_errors->AddFormat(_T("Internal error: %s opcode needs two operands."), opcode->ToString().c_str());
        } else {
            this->PopInput(code, inputs);
            this->PopInput(code, inputs);
            inputs->Push(new MathOpcode(MathOpcodeType::Nop));
        }
    }
    else if (opcode->GetType() == MathOpcodeType::SaveVariable)
    {
        if (inputs->Count() < 1) {
            m_errors->Add(_T("Internal error: SAV opcode needs one operand."));
        } else {
            this->PopInput(code, inputs);
        }
    }
    else if (opcode->GetType() == MathOpcodeType::Neg)
    {
        if (inputs->Count() < 1) {
            m_errors->Add(_T("Internal error: NEG opcode needs one operand."));
        } else {
            this->PopInput(code, inputs);
            inputs->Push(new MathOpcode(MathOpcodeType::Nop));
        }
    }
    else if (opcode->GetType() == MathOpcodeType::Double)
    {
        if (inputs->Count() < 1) {
            m_errors->Add(_T("Internal error: DBL opcode needs one operand."));
        } else {
            this->PopInput(code, inputs);
            inputs->Push(new MathOpcode(MathOpcodeType::Nop));
            inputs->Push(new MathOpcode(MathOpcodeType::Nop));
        }
    }
    else if (opcode->GetType() == MathOpcodeType::CallFunction)
    {
        int functionIndex = opcode->GetIndex();
        size_t args = m_functions->Item(functionIndex)->GetArgs();
        if (inputs->Count() < args) {
            m_errors->AddFormat(_T("Internal error: CALL opcode needs %u operands for the function."), args);
        } else {
            for (size_t i=0; i<args; ++i)
            {
                this->PopInput(code, inputs);
            }
            inputs->Push(new MathOpcode(MathOpcodeType::Nop));
        }
    }
    else if (opcode->GetType() == MathOpcodeType::Nop)
    {
        Console::WriteLine(_T("NOP operator"));
        code->Add(opcode);
    }
    else
    {
        Console::WriteLine(_T("Unexpected opcode: %s"), opcode->ToString().c_str());
    }

	// TODO : Move check to top of the method (allows diffrent types)
    if (checkPriority)
    {
        while (!operators->IsEmpty())
        {
            if (HasHigherPriority(opcode->GetType(), operators->Peek()->GetType()))
            {
                ResolveOperator(code, operators, inputs, false);
            }
            else
            {
                break;
            }
        }
    }
    code->Add(opcode);
}




//-----------------------------------------------------------------------------
MathOpcodeArray* MathEvaluation::CompileStep(MathTokenArray* tokens, size_t startIndex, size_t endIndex)
/**
 * \brief Compiles a single statement or parts of a statement. Brackets and functions
 * depth resolving will be resolved by recursive calls of this method.
 * \param tokens Token array.
 * \param startIndex Start index in the token array.
 * \param endIndex End index in the token array.
 **/
{
    // Loop through statements
    size_t indexToken = startIndex;
    MathOpcodeArray* opcodes = new MathOpcodeArray();
    ObjectDeque<MathOpcode>* operators = new ObjectDeque<MathOpcode>();
    ObjectDeque<MathOpcode>* inputs = new ObjectDeque<MathOpcode>();
    while (indexToken <= endIndex)
    {
        // Resolve assignment
        MathToken* token = tokens->Item(indexToken);
        MathOpcode* assignment = NULL;
        if (token->GetType() == MathTokenType::Assignment) {
            assignment = this->CreateOpcode(token);
            indexToken += 1;
        } else {
            //m_errors->Add(String::Format(_T("Statements must begin with an assignment.")));
        }

        // Resolve the rest of the statement
        token = tokens->Item(indexToken);
        while (indexToken <= endIndex)
        {
            if (token->GetType() == MathTokenType::Bracket)
            {
                if (token->GetContent() == _T("("))
                {
                    // Search for closing bracket
                    int indexOfClosing = FindClosingBracket(tokens, indexToken);
                    if (indexOfClosing < 0)
                    {
                        m_errors->Add(_T("Closing bracket is missing."));
                        indexToken++;
                        break;
                    }
                    else
                    {
                        MathOpcodeArray* opcodes = this->CompileStep(tokens, indexToken+1, indexOfClosing-1);
                        indexToken = indexOfClosing;
                        inputs->PushFront(new MathOpcode(MathOpcodeType::Opcodes, opcodes));
                    }
                }
                else
                {
                    m_errors->Add(_T("Unexpected closing bracket."));
                }
            }
            else if (token->GetType() == MathTokenType::Function)
            {
                // Push call operator as opcode into operators
                MathOpcodeArray* functionArray = new MathOpcodeArray();
                MathOpcode* functionOpcode = this->CreateOpcode(token);
                int functionIndex = this->GetFunctionIndex(token->GetContent());
                if (functionIndex < 0) {
                    indexToken += 1;
                    break;
                }

                // Check if function is valid
                indexToken += 1;
                token = tokens->Item(indexToken);
                if (token->GetType() != MathTokenType::Bracket || token->GetContent() != _T("("))
                {
                    m_errors->Add(_T("Bracket open expected after function name."));
                }
                else
                {
                    // Get the arguments count of the function
                    size_t args = m_functions->Item(functionIndex)->GetArgs();

                    // Find end bracket and commans of the function
                    size_t argsIndices[args];
                    if (!FindFunctionParts(tokens, indexToken, argsIndices, args))
                    {
                        m_errors->Add(String::Format(_T("Wrong number of arguments for function '%s'."),
                            m_functions->Item(functionIndex)->GetName().c_str()));
                        indexToken++;
                        break;
                    }

                    if (args > 0)
                    {
                        MathOpcodeArray* opcodes = this->CompileStep(tokens, indexToken+1, argsIndices[0]-1);
                        functionArray->AddRange(opcodes, true);
                        delete opcodes;
                        for (size_t i=1; i<args; ++i)
                        {
                            MathOpcodeArray* opcodes = this->CompileStep(tokens, argsIndices[i-1]+1, argsIndices[i]-1);
                            functionArray->AddRange(opcodes, true);
                            delete opcodes;
                        }
                        indexToken = argsIndices[args-1];
                    }
                    else
                    {
                        indexToken += 1;
                    }
                    functionArray->Add(functionOpcode);
                    inputs->PushFront(new MathOpcode(MathOpcodeType::Opcodes, functionArray));
                }
            }
            else if (token->GetType() == MathTokenType::Constant ||
                     token->GetType() == MathTokenType::Variable)
            {
                inputs->PushFront(this->CreateOpcode(token));
            }
            else if (token->GetType() == MathTokenType::Operator)
            {
                // Check if negative operator should be used
                MathToken* prevToken = tokens->Item(indexToken-1);
                if ((prevToken->GetType() == MathTokenType::Operator) ||
                    (prevToken->GetType() == MathTokenType::Assignment) ||
                    (prevToken->GetType() == MathTokenType::Bracket && prevToken->GetContent() == _T("(")))
                {
                    operators->PushFront(new MathOpcode(MathOpcodeType::Neg));
                }
                else if (token->GetContent() == _T("+-") || token->GetContent() == _T("--") ||
                         token->GetContent() == _T("*-") || token->GetContent() == _T("/-"))
                {
                    operators->PushFront(this->CreateOpcode(token));
                    operators->PushFront(new MathOpcode(MathOpcodeType::Neg));
                }
                else
                {
                    operators->PushFront(this->CreateOpcode(token));
                }
            }
            else if (token->GetType() == MathTokenType::EndStatement)
            {
                indexToken += 1;
                break;
            }
            else
            {
                m_errors->Add(_T("Internal error: Unexpected token type."));
            }
            indexToken += 1;
            token = tokens->Item(indexToken);
        }

        // Push the assignment operator
        if (assignment != NULL)
        {
            operators->PushFront(assignment);
        }

        // Create the stackbased code
        while (!operators->IsEmpty())
        {
            ResolveOperator(opcodes, operators, inputs, true);
        }
        while (!inputs->IsEmpty())
        {
            this->PopInput(opcodes, inputs);
        }
    }

    if (operators != NULL) delete operators;
    if (inputs != NULL) delete inputs;
    return (opcodes);
}




//-----------------------------------------------------------------------------
int MathEvaluation::GetVariableIndex(const String& name) const
/**
 * \brief Returns the index of a variable. Automatically creates the
 * variable if it does not exists.
 * \param name Variable name.
 * \return Variable index.
 **/
{
     // Search for the variable
    for (size_t i=0; i<m_variables->Count(); ++i)
    {
        if (m_variables->Item(i)->GetName() == name)
        {
            return (i);
        }
    }

    // Create the variable if it doesn't exist
    m_variables->Add(new MathVariable(name, 0.0d));
    return (m_variables->Count()-1);
}


//-----------------------------------------------------------------------------
int MathEvaluation::GetFunctionIndex(const String& name) const
/**
 * \brief Returns the index of a function or -1 if the function name
 * does not exists.
 * \param name Function name.
 * \return Function index or -1 if the function does not exist.
 **/
{
    for (size_t i=0; i<m_functions->Count(); ++i)
    {
        if (m_functions->Item(i)->GetName() == name)
        {
            return (i);
        }
    }
    return (-1);
}


//-----------------------------------------------------------------------------
MathOpcode* MathEvaluation::CreateOpcode(MathToken* token)
/**
 * \brief Creates an opcode from the given token. Tokens of type None,
 * Bracket and EndStatement will not create a opcode.
 * \param token Token.
 * \return Opcode.
 **/
{
    if (token->GetType() == MathTokenType::Assignment)
    {
        int index = this->GetVariableIndex(token->GetContent());
        if (index < 0) {
            m_errors->Add(String::Format(_T("Unknown variable name '%s'."), token->GetContent().c_str()));
            return (new MathOpcode(MathOpcodeType::Nop));
        }
        return (new MathOpcode(MathOpcodeType::SaveVariable, (size_t)index));
    }
    else if (token->GetType() == MathTokenType::Constant)
    {
        double value = Parser::ParseDouble(token->GetContent());
        return (new MathOpcode(MathOpcodeType::LoadConstant, value));
    }
    else if (token->GetType() == MathTokenType::Function)
    {
        int index = this->GetFunctionIndex(token->GetContent());
        if (index < 0) {
            m_errors->Add(String::Format(_T("Unknown function name '%s'."), token->GetContent().c_str()));
            return (new MathOpcode(MathOpcodeType::Nop));
        }
        return (new MathOpcode(MathOpcodeType::CallFunction, (size_t)index));
    }
    else if (token->GetType() == MathTokenType::Operator)
    {
        if (token->GetContent().StartsWith(_T("+"))) {
            return (new MathOpcode(MathOpcodeType::Add));
        }
        else if (token->GetContent().StartsWith(_T("-"))) {
            return (new MathOpcode(MathOpcodeType::Sub));
        }
        else if (token->GetContent().StartsWith(_T("*"))) {
            return (new MathOpcode(MathOpcodeType::Mul));
        }
        else if (token->GetContent().StartsWith(_T("/"))) {
            return (new MathOpcode(MathOpcodeType::Div));
        }
        m_errors->Add(String::Format(_T("Unknown operator '%s'."), token->GetContent().c_str()));
        return (new MathOpcode(MathOpcodeType::Nop));
    }
    else if (token->GetType() == MathTokenType::Variable)
    {
        int index = this->GetVariableIndex(token->GetContent());
        if (index < 0) {
            m_errors->Add(String::Format(_T("Unknown variable name '%s'."), token->GetContent().c_str()));
            return (new MathOpcode(MathOpcodeType::Nop));
        }
        return (new MathOpcode(MathOpcodeType::LoadVariable, (size_t)index));
    }
    else if (token->GetType() == MathTokenType::None)
    {
        m_errors->Add(_T("Cannot convert token 'None' to opcode."));
    }
    else if (token->GetType() == MathTokenType::EndStatement)
    {
        m_errors->Add(_T("Cannot convert token 'EndStatement' to opcode."));
    }
    else if (token->GetType() == MathTokenType::Bracket)
    {
        m_errors->Add(_T("Cannot convert token 'Bracket' to opcode."));
    }
    return (new MathOpcode(MathOpcodeType::Nop));
}



//-----------------------------------------------------------------------------
void MathEvaluation::OptimizeCode()
/**
 * \brief
 **/
{
    // Currently only optimization is the removing of the Nop OpCodes
    for (size_t i=0; i<m_opcodes->Count(); ++i)
    {
        MathOpcode* opcode = m_opcodes->Item(i);
        if (opcode->GetType() == MathOpcodeType::Nop)
        {
            delete opcode;
            (*m_opcodes)[i] = NULL;
        }
    }
    m_opcodes->MoveUp();

    // TODO : Calculate the max stack - Don't reallocate stack in execution
    // TODO : Calculate the constants - Example: a = 1+2; => a = 3;
    // TODO : Reduction of mathoperators
}



} // namespace rush


