ifeq ($(OS),Windows_NT)
	# NOTE: for this to work, docker-related commands need to have a pwsh equivalent alias
	SHELL := pwsh.exe
	.SHELLFLAGS := -Command
	BUILD_ENV :=
	n := \
else
	SHELL := /bin/sh
	BUILD_ENV := DOCKER_BUILDKIT=1
	n := `
	#` Nothing: this comment just helps with syntax highlighting a standalone backtick
endif

.PHONY: check-fmt help docker corpora fmt clippy clean clean-all

.DEFAULT_GOAL: docker-all

# NOTE: this works for windows too!
WORKSPACE_DIR := $(realpath workspace)

clients := lighthouse nimbus prysm teku lodestar
test_clients := $(addprefix test-,$(clients))
clean_clients := $(addprefix clean-,$(clients))


help:
	@echo 'Management commands for eth2fuzz'
	@echo
	@echo 'Available clients:'
	@echo '    lighthouse'
	@echo '    lodestar'
	@echo '    nimbus'
	@echo '    prysm'
	@echo '    teku'
	@echo
	@echo 'Basic Usage:'
	@echo
	@echo '    make fuzz-all                                    Build and fuzz all targets for all clients, 1 hr each.'
	@echo '    make fuzz-[CLIENT]                               Fuzz all targets for CLIENT, 1 hr each.'
	@echo '                                                     e.g. `make fuzz-lighthouse`'
	@echo '    make or make docker-all                          Build all docker images.'
	@echo '    make CLIENT                                      Build all docker image for CLIENT.'
	@echo '                                                     e.g. `make prysm`'
	@echo
	@echo '    make clean                                       Clean all (eth2fuzz && compiled fuzz target harnesses).'
	@echo '    make clean-[CLIENT]                              Clean build artifacts for a single client CLIENT.'
	@echo
	@echo 'Dev helpers:'
	@echo '    make test-all                                    Fuzz all targets for all clients, 1 s each.'
	@echo '    make test-[CLIENT]                               Fuzz all targets for CLIENT, 1 s each.'
	@echo
	@echo '    make corpora                                     Create initial corpora from Eth2 Spec tests.'
	@echo
	@echo '    make fmt                                         Run Rust fmt.'
	@echo
	@echo


# Create an initial corpora
corpora:
	cd workspace/corpora/ && ./extract_corpora_from_spectests.sh


#
# ALL CLIENTS
#

## Build all docker
docker-all: lighthouse lodestar nimbus prysm teku

## Fuzz all eth2 clients
fuzz-all: fuzz-lighthouse fuzz-lodestar fuzz-nimbus fuzz-prysm fuzz-teku

# Clean all (eth2fuzz && compiled fuzz target harnesses).
clean: clean-lighthouse clean-nimbus clean-prysm
	rm -rf workspace/debug/target
	# clean js - not needed
	# clean java libfuzzer - TODO

#
# Lighthouse
# https://github.com/sigp/lighthouse
#

## Fuzzing of lighthouse using docker.
lighthouse:
	$(BUILD_ENV) docker build $(n)
	--file docker/lighthouse.Dockerfile $(n)
	-t eth2fuzz_lighthouse $(n)
	. $(n)
	$(CACHE)
	@echo 'USAGE: docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lighthouse list'

## Fuzz all lighthouse targets for 1 hour each
fuzz-lighthouse: lighthouse
	docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lighthouse continuously -q lighthouse -t 3600 -n 1

## Try to run each target for 1 sec
test-lighthouse: lighthouse
	for i in $(shell docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lighthouse list); do $(n)
		docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lighthouse target $$i -t 1; $(n)
	done

## clean compiled fuzzing targets
clean-lighthouse:
	# clean lighthouse afl
	rm -rf workspace/afl/target
	# clean lighthouse hfuzz
	rm -rf workspace/hfuzz/hfuzz_target
	# clean lighthouse libfuzzer
	rm -rf workspace/libfuzzer/fuzz/target

#
# Lodestar
# https://github.com/ChainSafe/lodestar
#

## Fuzzing of lodestar using docker.
lodestar:
	$(BUILD_ENV) docker build $(n)
	--file docker/lodestar.Dockerfile $(n)
	-t eth2fuzz_lodestar $(n)
	. $(n)
	$(CACHE)
	@echo 'USAGE: docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lodestar list'

## Fuzz all lodestar targets for 1 hour each
fuzz-lodestar: lodestar
	docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lodestar continuously -q lodestar -t 3600

## Try to run each target for 1 sec
test-lodestar:
	for i in $(shell docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lodestar list); do $(n)
		docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_lodestar target $$i -t 1; test $$? -eq 1; $(n)
	done

## Nothing to clean with lodestar since there
## is not compiled fuzzing targets
clean-lodestar:

#
# Nimbus
# https://github.com/status-im/nim-beacon-chain
#

## Fuzzing of nim-beacon-chain using docker.
nimbus:
	$(BUILD_ENV) docker build $(n)
	--file docker/nimbus.Dockerfile $(n)
	-t eth2fuzz_nimbus $(n)
	. $(n)
	$(CACHE)
	@echo 'USAGE: docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_nimbus list'

## Fuzz all nimbus targets for 1 hour each
fuzz-nimbus: nimbus
	docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_nimbus continuously -q nimbus -t 3600

## Try to run each target for 1 sec
test-nimbus:
	for i in $(shell docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_nimbus list); do $(n)
		docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_nimbus target $$i -t 1; $(n)
	done

## clean compiled fuzzing targets
clean-nimbus:
	for i in $(shell docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_nimbus list); do $(n)
		rm -rf workspace/nimlibfuzzer/$$i; $(n)
	done

#
# Prysm
# https://github.com/prysmaticlabs/prysm
#

## Fuzzing of prysm using docker.
prysm:
	$(BUILD_ENV) docker build $(n)
	--file docker/prysm.Dockerfile $(n)
	-t eth2fuzz_prysm $(n)
	. $(n)
	$(CACHE)
	@echo 'USAGE: docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_prysm list'

## Fuzz all prysm targets for 1 hour each
fuzz-prysm: prysm
	docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_prysm continuously -q prysm -t 3600

## Try to run each target for 1 sec
test-prysm:
	for i in $(shell docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_prysm list); do $(n)
		docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_prysm target $$i -t 1; $(n)
	done

## clean compiled fuzzing targets
clean-prysm:
	# clean gofuzz libfuzzer
	rm -rf workspace/gofuzz/*.libfuzzer

#
# Teku
# https://github.com/PegaSysEng/teku
#

## Fuzzing of teku using docker.
teku:
	$(BUILD_ENV) docker build $(n)
	--file docker/teku.Dockerfile $(n)
	-t eth2fuzz_teku $(n)
	. $(n)
	$(CACHE)
	@echo 'USAGE: docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_teku list'

## Fuzz all teku targets for 1 hour each
fuzz-teku: teku
	docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_teku continuously -q teku -t 3600

## Try to run each target for 1 sec
test-teku:
	for i in $(shell docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_teku list); do $(n)
		docker run -v $(WORKSPACE_DIR):/eth2fuzz/workspace eth2fuzz_teku target $$i -t 1; test $$? -eq 1; $(n)
	done

## clean compiled fuzzing targets
clean-teku:
	# clean javafuzz
	rm -rf workspace/javafuzz/T*.class

#
# Developer utils
#

# Run Rust fmt to make code cleaner
fmt:
	cargo fmt --all

# Run Rust clippy to make code cleaner
clippy:
	cargo clippy --all
