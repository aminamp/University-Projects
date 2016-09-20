import types
import string
import copy
import sys

class Term:
    def __init__(self, function, parameter):
        self.function = function;
        self.parameters = parameter;

    @staticmethod
    def termToStr(term):
        t = ''
        t += term.function + '('
        for index in range(0, len(term.parameters)):
            if index < len(term.parameters) - 1:
                t += term.parameters[index] + ', '
            else:
                t += term.parameters[index] + ')'
        t += '\n'
        return t

    # @staticmethod
    # def printTerm(term):
    #     t = ''
    #     t += term.function + '('
    #     for index in range(0, len(term.parameters)):
    #         if index < len(term.parameters) - 1:
    #             t += term.parameters[index] + ', '
    #         else:
    #             t += term.parameters[index] + ')'
    #     print t,


class Rule:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

    @staticmethod
    def ruleToStr(rule):
        r = ''
        if len(rule.lhs) > 0:
            for term in rule.lhs:
                r += Term.termToStr(term)
            r += ' => '
        for term in rule.rhs:
            r += Term.termToStr(term)
        r += '\n'
        return r

    # @staticmethod
    # def printRule(rule):
    #     if len(rule.lhs) > 0:
    #         for term in rule.lhs:
    #             Term.printTerm(term)
    #         print " => ",
    #     for term in rule.rhs:
    #         Term.printTerm(term)
    #     print ""

class Substitution:
    def __init__(self, var, cons):
        self.variable = var
        self.constant = cons

    @staticmethod
    def printSubstitution(substition):
        print "{", substition.variable, "/", substition.constant, "}"

class FOLProblem:
    def __init__(self):
        self.goal = []
        self.KBSize = 0
        self.KB = []
        self.dataProcession()

    # read file and convert to data structure
    def dataProcession(self):
        try:
            # baseDir = "/Users/novelidea/Desktop/First-Order-Logic-Backward-Chaining-Algorithm/samples/"
            # data = open(baseDir + "sample05.txt")
            data = open(sys.argv[2])
            for index, line in enumerate(data):
                if index == 0 :
                    goal = self.lineToRule(line)
                    self.goal = goal.rhs
                elif index == 1 :
                    self.KBSize = int(line)
                else :
                    self.KB.append(self.lineToRule(line))
        except IOError as e:
            print(e)

    def lineToRule(self, line):
        line = line[0 : -1]
        ruleSet = line.split(" => ")

        if len(ruleSet) == 1 :
            ruleSet.insert(0, "")

        lhsSet = ruleSet[0].split(" && ")
        rhsSet = ruleSet[1].split(" && ")
        lhs = []
        rhs = []
        for element in lhsSet :
            if len(element) > 0 :
                lhs.append(self.stringToTerm(element))

        for element in rhsSet :
            if len(element) > 0 :
                rhs.append(self.stringToTerm(element))
        return Rule(lhs, rhs)

    def stringToTerm(self, str):
        if len(str) > 0:
            leftParenthesesIndex = str.index('(')
            function = str[0 : leftParenthesesIndex]
            parameters = str[leftParenthesesIndex + 1 : -1].split(', ')
            term = Term(function, parameters)
            return term
        return None

    def printProblem(self):
        print("==================================")
        for term in self.goal:
            Term.printTerm(term)
        print(self.KBSize)
        for kb in self.KB:
            Rule.printRule(kb)
        print("==================================")

class FOLBackwardChaining:

    def __init__(self):
        self.filePath = open('output.txt', 'w')
        self.functionParameterTable = {}
        self.paraNumberCarry = 0
        self.paraNumber = 0
        self.problem = FOLProblem()
        self.goal = copy.deepcopy(self.problem.goal)
        self.KB = copy.deepcopy(self.problem.KB)
        self.substitutions = []
        # self.goalTestCount = 0
        self.problem.goal = self.STANDARDIZE_INITIAL_GOAL(self.problem.goal)
        self.curASKResult = False

    # KB: set of rules; query: set of Terms
    def FOL_BC_ASK(self, KB, query):
        return self.FOL_BC_OR(KB, query, self.substitutions)


    # goal: set of Terms; substitutions: set of Substitutions
    def FOL_BC_OR(self, KB, goal, substitutions):
        for goalTerm in goal:
            goalTerm = self.SUBST(self.substitutions, goalTerm)
            goalTerm = goalTerm[0]

            termToBePrint = self.PRINT_VARIABLE_PROCESSION(copy.deepcopy(goalTerm))

            KB = copy.deepcopy(self.KB)

            rules = self.FETCH_RULES_FOR_GOAL(KB, goalTerm)

            if len(rules) == 0:
                ask = "Ask: " + Term.termToStr(termToBePrint)
                self.filePath.writelines(ask)
                false = "False: " + Term.termToStr(termToBePrint)

                self.filePath.writelines(false)
                if self.IS_LAST_GOALTERM(termToBePrint) is True:
                    self.curASKResult = False
                return

            endIndex = 0
            success = False
            for rule in rules:
                self.curASKResult = True
                ruleForTry = copy.deepcopy(rule)
                goalTermTry = copy.deepcopy(goalTerm)

                endIndex += 1
                ruleForTry = self.STANDARDIZE_VARIABLES(ruleForTry, goalTermTry)

                goalUnify = []
                goalUnify.append(goalTermTry)
                unifyResult = self.UNIFY(ruleForTry.rhs, goalUnify, substitutions)

                sub = self.FOL_BC_AND(KB, ruleForTry.lhs, unifyResult)

                ask = "Ask: " + Term.termToStr(termToBePrint)
                self.filePath.writelines(ask)


                if unifyResult is False:

                    false = "False: " + Term.termToStr(termToBePrint)
                    self.filePath.writelines(false)
                    if self.IS_LAST_GOALTERM(termToBePrint) is True:
                        self.curASKResult = True

                for substitution in sub:
                    success = True
                    goalTermTryPrint = copy.deepcopy(goalTermTry)

                    goalTermTryPrint = self.SUBST(self.substitutions, goalTermTryPrint)
                    goalTermTryPrint = goalTermTryPrint[0]


                    if self.TERM_IS_TRUE(goalTermTryPrint) is True:

                        ask = "True: " + Term.termToStr(goalTermTryPrint)
                        self.filePath.writelines(ask)
                        if self.IS_LAST_GOALTERM(goalTermTryPrint) is True:
                            self.curASKResult = True

                        self.REMOVE_SUBSTITUTIONS(goalTermTryPrint)

                    yield substitution
            if success == False:

                false = "False: " + Term.termToStr(termToBePrint)
                self.filePath.writelines(false)
                if self.IS_LAST_GOALTERM(termToBePrint) is True:
                    self.curASKResult = False
                    # self.filePath.writelines("False")
                    # self.filePath.close()
                    # return


    def FOL_BC_AND(self, KB, goals, substitutions):
        if substitutions == False:
            return
        elif len(goals) == 0:
            yield substitutions
        else:
            first, rest = goals[0], goals[1 : ]
            # IMPORTANT !!!
            firstTry = copy.deepcopy(first)
            tmp = self.SUBST(substitutions, firstTry)

            for substitution in self.FOL_BC_OR(self.problem.KB, tmp, substitutions):
                for subsubstitution in self.FOL_BC_AND(self.problem.KB, rest, substitution):
                    yield subsubstitution

    def IS_LAST_GOALTERM(self, term):

        lastGoalTerm = self.goal
        lastGoalTerm = lastGoalTerm[-1]

        if term.function != lastGoalTerm.function:
            return False
        if term.function == lastGoalTerm.function:
            for index in range(0, len(lastGoalTerm.parameters)):
                goalPara, termPara = lastGoalTerm.parameters[index], term.parameters[index]

                if self.VARIABLE(termPara) is True:
                    return False
                if self.VARIABLE(goalPara) is False and goalPara != termPara:
                    return False
        return True

    def REMOVE_SUBSTITUTIONS(self, term):
        for index in range(0, len(term.parameters)):
            if (term.function, index) in self.functionParameterTable:
                del self.functionParameterTable[(term.function, index)]
                # print "remove: ", (term.function, index)gi

    def FETCH_RULES_FOR_GOAL(self, KB, goal):
        rules = []
        KBFetch = copy.deepcopy(KB)
        for rule in KBFetch:
            for term in rule.rhs:
                if term.function == goal.function:
                    if self.UNIFY(term, goal, []) is not False:
                        rules.append(rule)
                        break
        return rules

    def RULE_IS_GOAL_FACT(self, rule, goalTerm):
        if self.RULE_IS_FACT(rule) is False:
            return False
        else:
            for term in rule.rhs:
                if term.function == goalTerm.function:
                    for i in range(0, len(term.parameters)):
                        termPara, goalPara = term.parameters[i], goalTerm.parameters[i]

                        if self.VARIABLE(goalPara) is False and termPara != goalPara:
                            return False
            return True

    def TERM_IS_TRUE(self, term):
        for parameter in term.parameters:
            if self.VARIABLE(parameter):
                return False
        return True

    def RULE_IS_FACT(self, rule):
        if len(rule.lhs) > 0:
            for term in rule.lhs:
                if self.TERM_IS_TRUE(term) is False:
                    return False
        if len(rule.rhs) > 0:
            for term in rule.rhs:
                if self.TERM_IS_TRUE(term) is False:
                    return False
        return True

    def PRINT_VARIABLE_PROCESSION(self, term):
        for index in range(0, len(term.parameters)):
                if self.VARIABLE(term.parameters[index]) is True:
                    term.parameters[index] = "_"
        return term

    def SUBST(self, substitutions, term):
        terms = []
        if len(substitutions) == 0:
            terms.append(term)
            return terms
        for substitution in substitutions:
            for i in range(len(term.parameters)):
                if term.parameters[i] == substitution.variable:
                    term.parameters[i] = substitution.constant
                    self.functionParameterTable.update({(term.function, i):'a'})
        terms.append(term)
        return terms

    def SUBST_TERMS(self, substitutions, terms):
        if len(substitutions) == 0:
            return terms
        for substitution in substitutions:
            for i in range(len(terms)):
                termList = self.SUBST(substitutions, terms[i])
                terms[i] = termList[0]
        return terms

    def SUBST_RULE(self, substitutions, rule):
        for substitution in substitutions:
            rule.lhs = self.SUBST_TERMS(substitutions, rule.lhs)
            rule.rhs = self.SUBST_TERMS(substitutions, rule.rhs)
        return rule

    def UNIFY(self, x, y, substitutions):
        if substitutions == False:
            return False
        elif x == y:
            return substitutions
        elif self.VARIABLE(x):
            return self.UNIFY_VAR(x, y, substitutions)
        elif self.VARIABLE(y):
            return self.UNIFY_VAR(y, x, substitutions)
        elif self.COMPOUND(x) and self.COMPOUND(y):
            return self.UNIFY(x.parameters, y.parameters, self.UNIFY(x.function, y.function, substitutions))
        elif type(x) is types.ListType and type(y) is types.ListType:
            return self.UNIFY(x[1 : ], y[1 :], self.UNIFY(x[0], y[0], substitutions))
        else:
            return False

    def UNIFY_VAR(self, x, y, substitutions):
        if substitutions.__contains__(Substitution(x, x)):
            return self.UNIFY(x, y, substitutions)
        elif substitutions.__contains__(Substitution(y, x)):
            return self.UNIFY(x, x, substitutions)
        elif self.OCCUR_CHECK(x, y, substitutions):
            return False
        else:
            # Update substitution
            for index in range(0, len(substitutions)):
                sub = substitutions[index]
                if sub.variable == x:
                    substitutions.remove(sub)
            substitutions.append(Substitution(x, y))

            return substitutions

    def OCCUR_CHECK(self, x, y, substitutions):
        for sub in substitutions:
            if x == sub.variable and y == sub.constant:
                return True
        return False

    def VARIABLE(self, x):
        if type(x) is not str:
            return False
        elif x[0] >= 'A' and x[0] <= 'Z':
            return False
        else:
            return True

    def COMPOUND(self, x):
        if type(x) is types.ListType:
            return False
        elif self.VARIABLE(x) is False and type(x) is not str:
            return True
        return False

    def STANDARDIZE_INITIAL_GOAL(self, terms):
        originalVarList = []
        substitution = []
        for term in terms:
            for index in range(0, len(term.parameters)):
                parameter = term.parameters[index]
                if self.VARIABLE(parameter) is False:
                    continue
                if parameter not in originalVarList:
                        replace = 'xpf' + 'a' * self.paraNumberCarry + string.lowercase[self.paraNumber]
                        substitution.append(Substitution(parameter, replace))
                        self.paraNumber += 1
                        if self.paraNumber >= 26:
                            self.paraNumber, self.paraNumberCarry = 0, self.paraNumberCarry + 1
        result = self.SUBST_TERMS(substitution, terms)
        return result

    def STANDARDIZE_VARIABLES(self, rule, goalTerm):
        originalVarList = []
        substitution = []
        for term in rule.rhs:
            if term.function == goalTerm.function:
                for index in range(0, len(term.parameters)):
                    termPara = term.parameters[index]
                    if self.VARIABLE(goalTerm.parameters[index]) is True and self.VARIABLE(termPara) is True:
                        substitution.append(Substitution(termPara, goalTerm.parameters[index]))
                        originalVarList.append(termPara)

        for terms in [rule.lhs, rule.rhs]:
            for term in terms:
                for index in range(0, len(term.parameters)):
                    parameter = term.parameters[index]
                    if self.VARIABLE(parameter) is False:
                        continue
                    elif parameter not in originalVarList:
                        replace = 'xpf' + 'a' * self.paraNumberCarry + string.lowercase[self.paraNumber]
                        substitution.append(Substitution(parameter, replace))

                        self.paraNumber += 1
                        if self.paraNumber >= 26:
                            self.paraNumber, self.paraNumberCarry = 0, self.paraNumberCarry + 1
        result = self.SUBST_RULE(substitution, rule)
        return result

if __name__ == '__main__':
    backChaining = FOLBackwardChaining()
    for index in range(0, len(backChaining.problem.goal)):
        goals = backChaining.problem.goal
        goal = []
        goal.append(goals[index])
        g = backChaining.FOL_BC_ASK(backChaining.problem.KB, goal)
        try:
            g.next()
        except StopIteration as e:
            print("")
        if backChaining.curASKResult == False:
            backChaining.filePath.writelines("False")
            break

    if backChaining.curASKResult == True:
        backChaining.filePath.writelines("True")