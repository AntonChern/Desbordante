#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "algorithms/gfd/gfd_validation.h"
#include "algorithms/gfd/pattern.h"
#include "algorithms/gfd/var_literal.h"
#include "algorithms/gfd/const_literal.h"

#define edge  std::pair<int, int>
#define attr  std::map<std::string, std::string>
#define field std::pair<int, std::string>

TEST(GFDValidationTest, TestTrivially) {
    std::map<int, std::string> vertices{
        {0, "quadrilateral"},
        {1, "parallelogram"},
        {2, "trapezoid"},
        {3, "rectangle"},
        {4, "rhombus"},
        {5, "square"}
    };
    std::map<edge, std::string> edges{
        {edge(0, 1), "two pairs of parallel sides"}, {edge(0, 2), "one pair of parallel sides"},
        {edge(1, 3), "equality of angles"}, {edge(1, 4), "equality of sides"},
        {edge(3, 5), "equality of sides"},
        {edge(4, 5), "equality of angles"}
    };
    std::map<int, attr> attributes{
        {0, attr{{"angles", "arbitrary"},      {"sides", "arbitrary"}}},
        {1, attr{{"angles", "pairwise equal"}, {"sides", "pairwise equal"}}},
        {2, attr{{"angles", "arbitrary"},      {"sides", "parallel and arbitrary"}}},
        {3, attr{{"angles", "equal"},          {"sides", "pairwise equal"}}},
        {4, attr{{"angles", "pairwise equal"}, {"sides", "equal"}}},
        {5, attr{{"angles", "equal"},          {"sides", "equal"}}}
    };
    Graph quadrilaterals = Graph(vertices, edges, attributes);

    std::map<int, std::string> pat_vertices{
        {0, "polygon"},
        {1, "triangle"},
    };
    std::map<edge, std::string> pat_edges{
        {edge(0, 1), "three sides"}
    };
    VarLiteral pat_literal = VarLiteral(field(0, "sides"), field(1, "sides"));
    Pattern pattern = Pattern(pat_vertices, pat_edges);
    std::vector<Literal> premises = std::vector<Literal>{};
    std::vector<Literal> conclusion = std::vector<Literal>{ pat_literal };
    GFD gfd = GFD(pattern, premises, conclusion);
    int expected_size = 1;

    auto algorithm = algos::GFDValidation(quadrilaterals, std::vector<GFD>{ gfd });
    algorithm.Execute();
    std::vector<GFD> GFDList = algorithm.GFDList();

    EXPECT_EQ(expected_size, GFDList.size());
    EXPECT_EQ(gfd.getPattern(), GFDList.at(0).getPattern());
}

TEST(GFDValidationTest, TestExistingMatches0) {
    std::map<int, std::string> nodes{
        {0, "person"}, {1, "film"}, {2, "film"}, {3, "film"}, {4, "film"},
        {5, "person"}, {6, "film"}, {7, "film"}, {8, "film"},
        {9, "person"}, {10, "film"}, {11, "film"}
    };
    std::map<edge, std::string> directed_ties{
        {edge(0, 1), "directed"}, {edge(0, 2), "directed"}, {edge(0, 3), "directed"}, {edge(0, 4), "directed"},
        {edge(5, 6), "directed"}, {edge(5, 7), "directed"}, {edge(5, 8), "directed"},
        {edge(9, 10), "directed"}, {edge(9, 11), "directed"}
    };
    std::map<int, attr> info{
        {0,  attr{{"name", "James Cameron"},   {"celebrity", "high"}}},
        {5,  attr{{"name", "Robert Zemeckis"}, {"celebrity", "high"}}},
        {9,  attr{{"name", "James Toback"},    {"celebrity", "low"}}},
        {1,  attr{{"year", "2009"}, {"success", "high"}, {"name", "Avatar"}}},
        {2,  attr{{"year", "1997"}, {"success", "high"}, {"name", "Titanic"}}},
        {3,  attr{{"year", "1981"}, {"success", "low"},  {"name", "Piranha II"}}},
        {4,  attr{{"year", "1984"}, {"success", "high"}, {"name", "Terminator"}}},
        {6,  attr{{"year", "2015"}, {"success", "high"}, {"name", "The Walk"}}},
        {7,  attr{{"year", "1985"}, {"success", "high"}, {"name", "Back to the future"}}},
        {8,  attr{{"year", "1994"}, {"success", "high"}, {"name", "Forrest Gump"}}},
        {10, attr{{"year", "2008"}, {"success", "high"}, {"name", "Tyson"}}},
        {11, attr{{"year", "1978"}, {"success", "high"}, {"name", "Fingers"}}}
    };
    Graph directors = Graph(nodes, directed_ties, info);

    std::map<int, std::string> pat_nodes{
        {0, "person"},
        {1, "film"}
    };
    std::map<edge, std::string> pat_directed_tie{
        {edge(0, 1), "directed"}
    };
    ConstLiteral premises_literal = ConstLiteral(field(0, "celebrity"), "high");
    ConstLiteral conclusion_literal = ConstLiteral(field(1, "success"), "high");
    Pattern pattern = Pattern(pat_nodes, pat_directed_tie);
    std::vector<Literal> premises = std::vector<Literal>{ premises_literal };
    std::vector<Literal> conclusion = std::vector<Literal>{ conclusion_literal };
    GFD connection_director_film = GFD(pattern, premises, conclusion);
    int expected_size = 0;

    auto algorithm = algos::GFDValidation(directors, std::vector<GFD>{ connection_director_film });
    algorithm.Execute();
    std::vector<GFD> GFDList = algorithm.GFDList();

    EXPECT_EQ(expected_size, GFDList.size());
}

TEST(GFDValidationTest, TestExistingMatches1) {
    std::map<int, std::string> people{
        {0, "person"}, {1, "person"}, {2, "person"}, {3, "person"}, {4, "person"},
        {5, "person"}, {6, "person"}, {7, "person"}, {8, "person"}, {9, "person"}
    };
    std::map<edge, std::string> family_ties{
        {edge(4, 0), "mom"}, {edge(4, 1), "dad"},
        {edge(5, 0), "mom"}, {edge(5, 1), "dad"},
        {edge(6, 2), "mom"}, {edge(6, 3), "dad"},
        {edge(7, 2), "mom"}, {edge(7, 3), "dad"},
        {edge(8, 5), "mom"}, {edge(8, 6), "dad"},
        {edge(9, 5), "mom"}, {edge(9, 6), "dad"}
    };
    std::map<int, attr> characteristics{
        {0, attr{{"name", "Milana"}, {"eyes", "brown"}, {"body_type", "mesomorph"}}},
        {1, attr{{"name", "Kirill"}, {"eyes", "brown"}, {"body_type", "ectomorph"}}},
        {2, attr{{"name", "Ksenia"}, {"eyes", "brown"}, {"body_type", "endomorph"}}},
        {3, attr{{"name", "Dmitry"}, {"eyes", "blue"},  {"body_type", "mesomorph"}}},
        {4, attr{{"name", "Nastya"}, {"eyes", "brown"}, {"body_type", "endomorph"}}},
        {5, attr{{"name", "Angela"}, {"eyes", "brown"}, {"body_type", "mesomorph"}}},
        {6, attr{{"name", "Daniil"}, {"eyes", "green"}, {"body_type", "mesomorph"}}},
        {7, attr{{"name", "Geralt"}, {"eyes", "blue"},  {"body_type", "mesomorph"}}},
        {8, attr{{"name", "Maksim"}, {"eyes", "green"}, {"body_type", "ectomorph"}}},
        {9, attr{{"name", "Matvey"}, {"eyes", "brown"}, {"body_type", "ectomorph"}}}
    };
    Graph family = Graph(people, family_ties, characteristics);

    std::map<int, std::string> pat_vertices0{
        {0, "person"},
        {1, "person"}
    };
    std::map<edge, std::string> pat_edges0{
        {edge(0, 1), "mom"}
    };
    ConstLiteral premises_literal0 = ConstLiteral(field(1, "eyes"), "brown");
    ConstLiteral conclusion_literal0 = ConstLiteral(field(0, "eyes"), "brown");
    Pattern pattern0 = Pattern(pat_vertices0, pat_edges0);
    std::vector<Literal> premises0 = std::vector<Literal>{ premises_literal0 };
    std::vector<Literal> conclusion0 = std::vector<Literal>{ conclusion_literal0 };
    GFD eyes_simple = GFD(pattern0, premises0, conclusion0);

    std::map<int, std::string> pat_vertices1{
        {0, "person"},
        {1, "person"},
        {2, "person"}
    };
    std::map<edge, std::string> pat_edges1{
        {edge(0, 1), "mom"},
        {edge(0, 2), "dad"}
    };
    ConstLiteral premises_literal11 = ConstLiteral(field(1, "eyes"), "brown");
    ConstLiteral premises_literal12 = ConstLiteral(field(2, "eyes"), "brown");
    ConstLiteral conclusion_literal1 = ConstLiteral(field(0, "eyes"), "brown");
    Pattern pattern1 = Pattern(pat_vertices1, pat_edges1);
    std::vector<Literal> premises1 = std::vector<Literal>{ premises_literal11, premises_literal12 };
    std::vector<Literal> conclusion1 = std::vector<Literal>{ conclusion_literal1 };
    GFD eyes_complex = GFD(pattern1, premises1, conclusion1);

    std::map<int, std::string> pat_vertices2{
        {0, "person"},
        {1, "person"},
        {2, "person"}
    };
    std::map<edge, std::string> pat_edges2{
        {edge(0, 1), "mom"},
        {edge(1, 2), "dad"}
    };
    VarLiteral conclusion_literal2 = VarLiteral(field(2, "body_type"), field(0, "body_type"));
    Pattern pattern2 = Pattern(pat_vertices2, pat_edges2);
    std::vector<Literal> premises2 = std::vector<Literal>{};
    std::vector<Literal> conclusion2 = std::vector<Literal>{ conclusion_literal2 };
    GFD body_types = GFD(pattern2, premises2, conclusion2);
    int expected_size = 2;

    auto algorithm = algos::GFDValidation(family, std::vector<GFD>{ eyes_simple, eyes_complex, body_types });
    algorithm.Execute();
    std::vector<GFD> GFDList = algorithm.GFDList();

    EXPECT_EQ(expected_size, GFDList.size());

    for (const GFD& current : GFDList) {
        EXPECT_FALSE(current.getPattern() == eyes_simple.getPattern());
    }
    EXPECT_FALSE(GFDList.begin()->getPattern() == (++GFDList.begin())->getPattern());

    for (const GFD& current : GFDList) {
        EXPECT_TRUE(
            current.getPattern() == eyes_complex.getPattern() ||
            current.getPattern() == body_types.getPattern()
        );
    }
}
