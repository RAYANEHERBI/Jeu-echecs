chess: main.o board.o view.o fen.o mask.o game.o echec.o historique.o
	g++ main.o board.o view.o fen.o mask.o game.o echec.o historique.o -o chess

main.o: main.cpp types.hpp board.hpp view.hpp mask.hpp game.hpp echec.hpp historique.hpp
	g++ -Wall -W -c main.cpp

board.o: board.cpp board.hpp types.hpp
	g++ -Wall -W -c board.cpp

view.o: view.cpp view.hpp types.hpp
	g++ -Wall -W -c view.cpp

mask.o: mask.cpp mask.hpp types.hpp board.hpp
	g++ -Wall -W -c mask.cpp

fen.o: fen.cpp fen.hpp types.hpp board.hpp
	g++ -Wall -W -c fen.cpp

game.o: game.cpp game.hpp types.hpp board.hpp mask.hpp echec.hpp historique.hpp
	g++ -Wall -W -c game.cpp

echec.o: echec.cpp echec.hpp types.hpp board.hpp
	g++ -Wall -W -c echec.cpp

historique.o: historique.cpp historique.hpp types.hpp board.hpp view.hpp
	g++ -Wall -W -c historique.cpp



test_read_fen.o: test_read_fen.cpp types.hpp board.hpp view.hpp fen.hpp
	g++ -Wall -W -c test_read_fen.cpp

test_write_fen.o: test_write_fen.cpp types.hpp board.hpp fen.hpp
	g++ -Wall -W -c test_write_fen.cpp

test_historique.o: test_historique.cpp types.hpp board.hpp view.hpp historique.hpp
	g++ -Wall -W -c test_historique.cpp

test_king_in_check.o: test_king_in_check.cpp types.hpp board.hpp view.hpp echec.hpp
	g++ -Wall -W -c test_king_in_check.cpp

test_king_in_check_computer.o: test_king_in_check_computer.cpp types.hpp board.hpp view.hpp game.hpp echec.hpp
	g++ -Wall -W -c test_king_in_check_computer.cpp

test_king_in_checkmate.o: test_king_in_checkmate.cpp types.hpp board.hpp view.hpp echec.hpp
	g++ -Wall -W -c test_king_in_checkmate.cpp


test_read_fen: test_read_fen.o board.o view.o fen.o
	g++ test_read_fen.o board.o view.o fen.o -o test_read_fen

test_write_fen: test_write_fen.o board.o fen.o
	g++ test_write_fen.o board.o fen.o -o test_write_fen

test_historique: test_historique.o board.o view.o historique.o
	g++ test_historique.o board.o view.o historique.o -o test_historique

test_king_in_check: test_king_in_check.o board.o view.o mask.o echec.o
	g++ test_king_in_check.o board.o view.o mask.o echec.o -o test_king_in_check

test_king_in_check_computer: test_king_in_check_computer.o board.o view.o mask.o game.o echec.o
	g++ test_king_in_check_computer.o board.o view.o mask.o game.o echec.o -o test_king_in_check_computer

test_king_in_checkmate: test_king_in_checkmate.o board.o view.o mask.o echec.o
	g++ test_king_in_checkmate.o board.o view.o mask.o echec.o -o test_king_in_checkmate


clean:
	rm -f *.o chess test_read_fen test_write_fen test_historique test_king_in_check test_king_in_check_computer test_king_in_checkmate