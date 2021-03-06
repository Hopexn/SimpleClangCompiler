#ifndef COMPILER_ABS_HPP
#define COMPILER_ABS_HPP

#include "util.hpp"

typedef enum {
    ENUM_assignment_expression,
    ENUM_primary_expression,
    ENUM_constant,
    ENUM_function_invoking,
    ENUM_argue_list,
    ENUM_compound_expression,
    ENUM_declaration_list,
    ENUM_declaration,
    ENUM_type_specifier,
    ENUM_init_declarator_list,
    ENUM_statement_list,
    ENUM_statement,
    ENUM_block_statement,
    ENUM_expression_statement,
    ENUM_selection_statement,
    ENUM_iteration_statement,
    ENUM_jump_statement,
    ENUM_program,
    ENUM_function_definition_list,
    ENUM_function_definition,
    ENUM_parameter_list,
    ENUM_ID,
    ENUM_IVAL,
    ENUM_FVAL,
    ENUM_CVAL
} ABS_node_type;

typedef _ABS_ID ABS_ID;
struct _ABS_ID {
    string id;
};

ABS_ID F_ABS_ID(string id) {
    ABS_ID abs_id = (ABS_ID) check_malloc(*abs_id);
    abs_id.id = id;
    return abs_id;
}

typedef _ABS_IVAL ABS_IVAL;
struct _ABS_IVAL {
    int ival;
};

ABS_IVAL F_ABS_IVAL(int ival) {
    ABS_IVAL abs_ival = (ABS_IVAL) check_malloc(*abs_ival);
    abs_ival.ival = ival;
    return abs_ival;
}

typedef _ABS_FVAL ABS_FVAL;
struct _ABS_FVAL {
    float fval;
};

_ABS_FVAL F_ABS_FVAL(float fval) {
    ABS_FVAL abs_fval = (ABS_FVAL) check_malloc(*abs_fval);
    abs_fval.fval = fval;
    return abs_fval;
}

typedef _ABS_CVAL ABS_CVAL;
struct _ABS_CVAL {
    float fval;
};

_ABS_CVAL F_ABS_CVAL(char cval) {
    ABS_CVAL abs_cval = (ABS_CVAL) check_malloc(*abs_cval);
    abs_cval.cval = cval;
    return abs_cval;
}

typedef _ABS_expression_list *ABS_expression_list;
struct _ABS_expression_list {
    vector<ABS_expression> expression_list;
};

ABS_expression_list F_ABS_expression_list(ABS_expression_list expression_list,
                                          ABS_expression expression) {
    if (expression_list == NULL) {
        expression_list = (ABS_expression_list) check_malloc(sizeof(*expression_list));
    }
    expression_list->expression_list.push_back(expression);
    return expression_list;
}

typedef _ABS_expression *ABS_expression;
struct _ABS_expression {
    enum ABS_node_type type;
    union {
        ABS_assignment_expression assignment_expression;
        ABS_compound_expression compound_expression;
    };
};

ABS_expression F_ABS_expression(ABS_node_type type,
                                ABS_assignment_expression assignment_expression,
                                ABS_compound_expression compound_expression) {
    ABS_expression expression = (ABS_expression) check_malloc(sizeof(*expression));
    switch (type) {
        case ENUM_assignment_expression:
            assert(assignment_expression);
            expression->assignment_expression = assignment_expression;
            break;
        case ENUM_compound_expression:
            assert(assignment_expression);
            expression->compound_expression = assignment_expression;
            break;
        default:
            yyerror("Undefined type");
            exit(0);
    }
    return expression;
}


typedef _ABS_assignment_expression *ABS_assignment_expression;
struct _ABS_assignment_expression {
    ABS_ID abs_id;
    ABS_compound_expression compound_expression_index;
    ABS_compound_expression compound_expression_value;
};

ABS_assignment_expression F_ABS_assignment_expression(ABS_ID abs_id,
                                                      ABS_compound_expression compound_expression_index,
                                                      ABS_compound_expression compound_expression_value) {
    ABS_assignment_expression assignment_expression = (ABS_assignment_expression) check_malloc(
            sizeof(*assignment_expression));
    assignment_expression->abs_id = abs_id;
    assignment_expression->compound_expression_index = compound_expression_index;
    assignment_expression->compound_expression_value = compound_expression_value;
    return assignment_expression;
}

typedef _ABS_primary_expression *ABS_primary_expression;
struct _ABS_primary_expression {
    ABS_node_type type;
    union {
        ABS_ID id;
        ABS_constant constant;
        ASB_compound_expression compound_expression;
        ABS_function_invoking function_invoking;
    };
};

ABS_primary_expression F_ABS_primary_expression(ABS_node_type type,
                                                ABS_ID id, ABS_constant constant,
                                                ASB_compound_expression compound_expression,
                                                ABS_function_invoking function_invoking) {
    ABS_primary_expression primary_expression = (ABS_primary_expression) check_malloc(*primary_expression);
    switch (type) {
        case ENUM_ID:
            primary_expression->id = id;
            break;
        case ENUM_constant:
            primary_expression->constant = constant;
            break;
        case ENUM_compound_expression:
            primary_expression->compound_expression = compound_expression;
            break;
        case ENUM_function_invoking:
            primary_expression->function_invoking = function_invoking;
            break;
        default:
            yyerror("Undefined type");
            exit(0);
    }
    return primary_expression;
}

typedef _ABS_constant *ABS_constant;
struct _ABS_constant {
    ABS_node_type type;
    union {
        ABS_IVAL abs_ival;
        ABS_FVAL abs_fval;
        ABS_CVAL abs_cval;
    };
};

ABS_constant F_ABS_constant(ABS_node_type type,
                            ABS_IVAL abs_ival,
                            ABS_FVAL abs_ival,
                            ABS_CVAL abs_cval) {
    ABS_constant constant = (ABS_constant) check_malloc(sizeof(*constant));
    switch (type) {
        case ENUM_IVAL:
            constant->abs_ival = abs_ival;
            break;
        case ENUM_FVAL:
            constant->abs_fval = abs_fval;
            break;
        case ENUM_CVAL:
            constant->abs_cval = abs_cval;
            break;
        default:
            yerror("Undefined type");
            exit(0);
    }
    return constant;
}

typedef _ABS_function_invoking *ABS_function_invoking;
struct _ABS_function_invoking {
    ABS_ID abs_id;
    ABS_argue_list argue_list;
};

ABS_function_invoking F_ABS_function_invoking(
        ABS_ID abs_id,
        ABS_argue_list argue_list
) {
    ABS_function_invoking function_invoking = (ABS_function_invoking) check_malloc(sizeof(*function_invoking));
    function_invoking->abs_id = abs_id;
    function_invoking->argue_list = argue_list;
    return function_invoking;
}

typedef _ABS_argue_list *ABS_argue_list;
struct _ABS_argue_list {
    vector<ABS_ID> list;
};

ABS_argue_list F_ABS_argue_list(ABS_argue_list argue_list, ABS_ID abs_id) {
    if (argue_list == NULL) {
        argue_list = (ABS_argue_list) check_malloc(sizeof(*argue_list));
    }
    argue_list->list.push_back(abs_id);
    return argue_list;
}

typedef enum {
    ENUM_NONE,
    ENUM_MUL,
    ENUM_DIV,
    ENUM_MOD,
    ENUM_PLUS,
    ENUM_MINUS,
    ENUM_LT,
    ENUM_GT,
    ENUM_LE,
    ENUM_GE,
    ENUM_EQ,
    ENUM_NE,
    ENUM_AND,
    ENUM_OR
} ENUM_oper_type;


typedef enum {
    ENUM_INT,
    ENUM_FLOAT,
    ENUM_CHAR
} ENUM_type_specifier;

typedef _ABS_compound_expression *ABS_compound_expression;
struct _ABS_compound_expression {
    ENUM_oper_type oper_type;
    ABS_primary_expression primary_expression;
    ABS_compound_expression compound_expression;
};

ABS_compound_expression F_ABS_compound_expression(
        ENUM_oper_type oper_type,
        ABS_primary_expression primary_expression,
        ABS_compound_expression compound_expression
) {
    ABS_compound_expression compound_expression = (ABS_compound_expression) check_malloc(sizeof(*compound_expression));
    compound_expression->oper_type = oper_type;
    compound_expression->primary_expression = primary_expression;
    compound_expression->compound_expression = compound_expression;
    return compound_expression;
}

typedef _ABS_declaration_list *ABS_declaration_list;
struct _ABS_declaration_list {
    vector<declaration> declaration_list;
};

ABS_declaration_list F_ABS_declaration_list(
        ABS_declaration_list declaration_list,
        ABS_declaration declaration) {
    if (declaration_list == NULL) {
        declaration_list = (ABS_declaration_list) check_malloc(sizeof(*declaration_list));
    }
    declaration_list->declaration_list.push_back(declaration);
    return declaration_list;
}

typedef _ABS_declaration *ABS_declaration;
struct _ABS_declaration {
    ABS_type_specifier type_specifier;
    ABS_init_declarator_list init_declarator_list;
};

ABS_declaration F_ABS_declaration(ABS_type_specifier type_specifier,
                                  ABS_init_declarator_list init_declarator_list) {
    ABS_declaration declaration = (ABS_declaration) check_malloc(sizeof(*declaration));
    declaration->type_specifier = type_specifier;
    declaration->init_declarator_list = init_declarator_list;
    return declaration;
}

typedef _ABS_type_specifier *ABS_type_specifier;
struct _ABS_type_specifier {
    ENUM_type_specifier type;
};

ABS_type_specifier F_ABS_type_specifier(ENUM_type_specifier type) {
    ABS_type_specifier type_specifier = (ABS_type_specifier) check_malloc(sizeof(*type_specifier));
    type_specifier->type = type;
    return type_specifier;
}

typedef _ABS_init_declarator_list *ABS_init_declarator_list;
struct _ABS_init_declarator_list {
    vector<ABS_init_declarator> init_declarator_list;
};

ABS_init_declarator_list F_ABS_init_declarator_list(
        ABS_init_declarator_list init_declarator_list,
        ABS_init_declarator init_declarator
) {
    if (init_declarator_list == NULL) {
        init_declarator_list = (ABS_init_declarator_list) check_malloc(
                sizeof(*init_declarator_list));
    }
    init_declarator_list->init_declarator_list.push_back(init_declarator);
    return init_declarator;
}


typedef _ABS_init_declarator *ABS_init_declarator;
struct _ABS_init_declarator {
    ABS_ID id;
    ABS_constant constant;
};

ABS_init_declarator F_ABS_init_declarator(
        ABS_ID id,
        ABS_constant constant
) {
    ABS_init_declarator init_declarator = (ABS_init_declarator) check_malloc(sizeof(*init_declarator));
    init_declarator->id = id;
    init_declarator->constant = constant;
}

typedef _ABS_statement_list *ABS_statement_list;
struct _ABS_statement_list {
    vector<ABS_statement> statement_list;
};

ABS_statement_list F_ABS_statement_list(
        ABS_statement_list statement_list,
        ABS_statement statement
) {
    if (statement_list == NULL) {
        statement_list = (ABS_statement_list) check_malloc(
                sizeof(*statement_list));
    }
    statement_list->statement_list.push_back(statement);
    return statement_list;
}

typedef _ABS_statement *ABS_statement;
struct _ABS_statement {
    ENUM_node_type type;
    union {
        ABS_block_statement block_statement;
        ABS_expression_statement expression_statement;
        ABS_selection_statement selection_statement;
        ABS_iteration_statement iteration_statement;
        ABS_jump_statement jump_statement;
        ABS_compound_expression compound_expression;
    };
};

ABS_statement F_ABS_statement(
        ENUM_node_type type,
        ABS_block_statement block_statement,
        ABS_expression_statement expression_statement,
        ABS_selection_statement selection_statement,
        ABS_iteration_statement iteration_statement,
        ABS_jump_statement jump_statement,
        ABS_compound_expression compound_expression
) {
    ABS_statement statement = (ABS_statement) check_malloc(sizeof(*statement));
    statement->type = type;
    switch (type) {
        case ENUM_block_statement:
            statement->block_statement = block_statement;
            break;
        case ENUM_expression_statement :
            statement->expression_statement = expression_statement;
            break;
        case ENUM_selection_statement:
            statement->selection_statement = selection_statement;
            break;
        case ENUM_iteration_statement:
            statement->iteration_statement = iteration_statement;
            break;
        case ENUM_jump_statement:
            statement->jump_statement = jump_statement;
            break;
        case ENUM_compound_expression:
            statement->compound_expression = compound_expression;
            break;
        default:
            yyerror("Undefined type");
            exit(0);
    }
    return statement;
}

typedef _ABS_block_statement *ABS_block_statement;
struct _ABS_block_statement {
    ABS_declaration_list declaration_list;
    ABS_statement_list statement_list;
};

ABS_block_statement F_ABS_block_statement(
        ABS_declaration_list declaration_list,
        ABS_statement_list statement_list
) {
    ABS_block_statement block_statement = (ABS_block_statement) check_malloc(sizeof(*block_statement));
    block_statement->declaration_list = declaration_list;
    block_statement->statement_list = statement_list;
    return block_statement;
}

typedef _ABS_expression_statement *ABS_expression_statement;
struct _ABS_expression_statement {
    ABS_expression_list expression_list
    expression_list;
};

ABS_expression_statement F_ABS_expression_statement(
        ABS_expression_list expression_list
) {
    ABS_expression_statement expression_statement = (ABS_expression_statement) check_malloc(
            sizeof(*expression_statement));
    expression_statement->expression_list = expression_list;
    return expression_statement;
}

typedef _ABS_selection_statement *ABS_selection_statement;
struct _ABS_selection_statement {
    ABS_expression_list expression_list;
    ABS_statement statement_if;
    ABS_statement statement_else;
};

ABS_selection_statement F_ABS_selection_statement(
        ABS_expression_list expression_list,
        ABS_statement statement_if,
        ABS_statement statement_else
) {
    ABS_selection_statement selection_statement = (ABS_selection_statement) check_malloc(sizeof(*selection_statement));
    selection_statement->expression_list = expression_list;
    selection_statement->statement_if = statement_if;
    selection_statement->statement_else = statement_else;
    return selection_statement;
}

typedef _ABS_iteration_statement *ABS_iteration_statement;
struct _ABS_iteration_statement {
    ABS_expression_list expression_list_while;

    ABS_expression_statement expression_statement_for_left;
    ABS_expression_statement expression_statement_for_middle;
    ABS_expression_list expression_list_for_right;

    ABS_statement statement;
};

ABS_iteration_statement F_ABS_iteration_statement(
        ABS_expression_list expression_list_while,
        ABS_expression_statement expression_statement_for_left,
        ABS_expression_statement expression_statement_for_middle,
        ABS_expression_list expression_list_for_right,
        ABS_statement statement

) {
    ABS_iteration_statement iteration_statement = (ABS_iteration_statement) check_malloc(sizeof(*iteration_statement));
    iteration_statement->expression_list_while = expression_list_while;
    iteration_statement->expression_statement_for_left = expression_statement_for_left;
    iteration_statement->expression_statement_for_middle = expression_statement_for_middle;
    iteration_statement->expression_list_for_right = expression_list_for_right;
    iteration_statement->statement = statement;
    return iteration_statement;
}

typedef _ABS_jump_statement *ABS_jump_statement;
typedef enum {
    ENUM_BREAK,
    ENUM_CONTINUE,
    ENUM_RETURN
} ENUM_action_type;
struct _ABS_jump_statement {
    ENUM_action_type action_type;
    ABS_expression_statement expression_statement;
};

ABS_jump_statement F_ABS_jump_statement(
        ENUM_action_type action_type,
        ABS_expression_statement expression_statement
) {
    ABS_jump_statement jump_statement = (ABS_jump_statement) check_malloc(sizeof(*jump_statement));
    jump_statement->action_type = action_type;
    jump_statement->expression_statement = expression_statement;
    return jump_statement;
}

typedef _ABS_program *ABS_program;
struct _ABS_program {
    ABS_declaration_list declaration_list;
    ABS_function_definition_list function_definition_list;
};

ABS_program F_ABS_program(
        ABS_declaration_list declaration_list,
        ABS_function_definition_list function_definition_list
) {
    ABS_program program = (ABS_program) malloc(sizeof(*program));
    program->declaration_list = declaration_list;
    program->function_definition_list = function_list;
    return program;
}

typedef _ABS_function_definition_list *ABS_function_definition_list;
struct _ABS_function_definition_list {
    vector<ABS_function_definition> function_definition_list;
};

ABS_function_definition_list F_ABS_function_definition_list(
        ABS_function_definition_list function_definition_list,
        ABS_function_definition function_definition
) {
    if (function_definition_list == null) {
        function_definition_list = (ABS_function_definition_list) check_malloc(sizeof(*function_definition_list));
    }
    function_definition_list->function_definition_list.push_back(function_definition);
    return function_definition_list;
}

typedef _ABS_function_definition *ABS_function_definition;
struct _ABS_function_definition {
    ABS_type_specifier type_specifier;
    ABS_ID id;
    ABS_parameter_list parameter_list;
    ABS_block_statement block_statement;
};

ABS_function_definition F_ABS_function_definition(
        ABS_type_specifier type_specifier,
        ABS_ID id,
        ABS_parameter_list parameter_list,
        ABS_block_statement block_statement
) {
    ABS_function_definition function_definition = (ABS_function_definition) check_malloc(sizeof(*function_definition));
    function_definition->type_specifier = type_specifier;
    function_definition->id = id;
    function_definition->parameter_list = parameter_list;
    function_definition->block_statement = block_statement;
    return function_definition;
}

typedef _ABS_parameter_list *ABS_parameter_list;
struct _ABS_parameter_list {
    vector<ABS_parameter> parameter_list;
};

ABS_parameter_list F_ABS_parameter_list(
        ABS_parameter_list parameter_list,
        ABS_parameter parameter
) {
    if (parameter_list == NULL) {
        parameter_list = (ABS_parameter_list) check_malloc(sizeof(*parameter_list));
    }
    parameter_list->parameter_list.push_back(parameter);
    return parameter_list;
}

typedef _ABS_parameter *ABS_parameter;
struct _ABS_parameter {
    ABS_type_specifier type_specifier;
    ABS_ID id;
};

ABS_parameter F__ABS_parameter(
        ABS_type_specifier type_specifier,
        ABS_ID id
) {
    ABS_parameter parameter = (ABS_parameter) check_malloc(sizeof(*parameter));
    parameter->type_specifier = type_specifier;
    parameter->id = id;
    return parameter;
}

#endif //COMPILER_ABS_HPP