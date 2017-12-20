#
#  Makefile
#
#  A Cognitive Information Theory of Music
#
#  Copyright (C) 2006, 2017 Tak-Shing Chan
#

all:
	@echo -----------------------------------------
	@echo  A Cognitive Information Theory of Music
	@echo           Tak-Shing Thomas Chan
	@echo -----------------------------------------
	$(MAKE) -C information/chan/ncf-ftd
	$(MAKE) -C information/chan/plain-ftd

reproduce:
	@echo -----------------------------------------
	@echo  Chapter 3. Cognitive Information
	@echo -----------------------------------------
	cd information/conley     && ./experiment-1
	cd information/conley     && ./experiment-2
	cd information/heyduk     && ./experiment-1
	cd information/shmulevich && ./experiment-1
	@echo -----------------------------------------
	@echo  Chapter 4. Musical Similarity
	@echo -----------------------------------------
	cd similarity && ./experiment-1
	cd similarity && ./experiment-2
	cd similarity && ./experiment-3
	@echo -----------------------------------------
	@echo  Chapter 5. Musical Fitness
	@echo -----------------------------------------
	cd fitness && ./experiment-1
	cd fitness && ./experiment-2
	cd fitness && ./experiment-3
	cd fitness && ./experiment-4
	cd fitness && ./experiment-5

regenerate:
	@echo -----------------------------------------
	@echo  Compiling Utilities
	@echo -----------------------------------------
	$(MAKE) -C utilities/melisma2003/meter
	$(MAKE) -C utilities/dcmt0.1/lib
	$(MAKE) -C utilities
	@echo -----------------------------------------
	@echo  Regenerating Stimuli
	@echo -----------------------------------------
	cd fitness && ./genstimulus-1
	cd fitness && ./genstimulus-2
	cd fitness && ./genstimulus-5
