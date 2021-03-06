/**
 * @file Calculator.c
 * @author: Zhang Hai
 */

/*
 * Copyright (C) 2014 Zhang Hai
 *
 * This file is part of calc.
 *
 * calc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * calc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with calc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "zhclib/Common.h"
#include "zhclib/Console.h"

#include "Evaluator.h"


string EVALUATION_RESULTS[] = {
    "EVALUATION_SUCCESS",
    "EVALUATION_ERROR_MALFORMED_EXPRESSION",
    "EVALUATION_ERROR_COMMA_NOT_IN_FUNCTION",
    "EVALUATION_ERROR_UNPAIRED_PARENTHESIS",
    "EVALUATION_ERROR_PARSING_FAILED",
    "EVALUATION_ERROR_FINALIZATION_FAILED",
    "EVALUATION_ERROR_INVALID_OPERATION",
    "EVALUATION_ERROR_INTERNAL_FAILURE"
};


void welcome() {
    Console_print(
            "calc - A simple calculator based on stack.\n"
            "Copyright (C) 2014, Zhang Hai.\n"
            "Powered by zhclib.\n"
            "\n"
            "This program comes with ABSOLUTELY NO WARRANTY.\n"
            "This is free software, and you are welcome to redistribute it\n"
            "under GNU General Public License v3.0.\n"
            "\n"
            "Press <Enter> to evaluate an expression;\n"
            "Enter an empty line to quit.\n"
            "\n");
}

int main() {

    string line;
    double value;
    EvaluationResult result;

    welcome();

    while (!string_isEmpty(line = Console_readLine("> "))) {
        result = evaluateExpression(line, &value);
        Memory_free(line);
        if (result == EVALUATION_SUCCESS) {
            Console_printLine("%.10g", value);
        } else {
            Console_printErrorLine("Error %d: %s", result,
                    EVALUATION_RESULTS[result]);
        }
    }
    Memory_free(line);

    return 0;
}
