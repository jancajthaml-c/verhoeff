OUTDIR=pkg
MODULE=verhoeff

.PHONY: default clean

default: test clean

$(OUTDIR):
	@mkdir -p $(OUTDIR)

test: $(OUTDIR) $(OUTDIR)/$(MODULE).o $(OUTDIR)/$(MODULE)_o2.o $(OUTDIR)/$(MODULE)_o3.o $(OUTDIR)/main.o
	gcc $(OUTDIR)/$(MODULE).o $(OUTDIR)/main.o -o $(OUTDIR)/$(MODULE)
	gcc -o2 $(OUTDIR)/$(MODULE)_o2.o $(OUTDIR)/main.o -o $(OUTDIR)/test_o2
	gcc -o3 $(OUTDIR)/$(MODULE)_o3.o $(OUTDIR)/main.o -o $(OUTDIR)/test_o3
	@echo "\ntest [human optimised]"
	@./$(OUTDIR)/$(MODULE) || echo "failed"
	@echo "\ntest [automatic optimalisation level 2]"
	@./$(OUTDIR)/test_o2 || echo "failed"
	@echo "\ntest [automatic optimalisation level 3]"
	@./$(OUTDIR)/test_o3 || echo "failed"

$(OUTDIR)/$(MODULE).o: src/$(MODULE).c
	gcc -o $(OUTDIR)/$(MODULE).o -c $^

$(OUTDIR)/$(MODULE)_o2.o: src/$(MODULE).c
	gcc -o2 -o $(OUTDIR)/$(MODULE)_o2.o -c $^

$(OUTDIR)/$(MODULE)_o3.o: src/$(MODULE).c
	gcc -o3 -o $(OUTDIR)/$(MODULE)_o3.o -c $^

$(OUTDIR)/main.o: src/main.c
	gcc -o $(OUTDIR)/main.o -c $^

clean:
	@rm -rf $(OUTDIR)
